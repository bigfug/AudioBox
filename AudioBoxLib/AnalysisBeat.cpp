#include "StdAfx.h"
#include "AnalysisBeat.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

AnalysisBeat::AnalysisBeat( void )
: mBeatLocked( false ), mBeatOffset( 0 )
{
	mBpm = mLastBpm = BPM_START;
	mBeatLength = bpm2ms( BPM_START );
	mIsBeat = false;
}

AnalysisBeat::~AnalysisBeat( void )
{
}

void AnalysisBeat::reset( void )
{
	mBpm = mLastBpm = mCalcBpm = BPM_START;
	mBeatLength = bpm2ms( BPM_START );
	mIsBeat = false;
	mCalcTempoConfidence = 0.0f;
	mCalcSyncConfidence = 0.0f;
	mBeatsAdded = 0;

	mBpmCur    = BPM_START;
	mBpmCurCnt = BPM_MAX_CNT;

	for( int i = 0 ; i < BPM_NEW_CNT ; i++ )
	{
		mBpmNew[ i ]    = 0;
		mBpmNewCnt[ i ] = 0;
	}

	mBpmMin = 40;
	mBpmMax = 180;

	mBeatOffset = 0.0;

	mBeat = 0;
}

bool AnalysisBeat::initialise( const int pSampleRate, const int pSamplesPerFrame )
{
	Analysis::initialise( pSampleRate, pSamplesPerFrame );

	mInBeat = false;
	mIsBeat = false;

	reset();

	mAnalysisTempo.initialise( pSampleRate, pSamplesPerFrame );

	return( true );
}

void AnalysisBeat::deinitialise( void )
{
	Analysis::deinitialise();

	mAnalysisTempo.deinitialise();
}

void AnalysisBeat::processData( float pValue, float pAverage, PtTimestamp pTimeStamp, long pWindowSize )
{
	mBeatStart = false;

	if( pValue > pAverage )
	{
		if( !mInBeat )
		{
			mBeatMax       = pValue;
			mBeatRelMax    = pValue - pAverage;
			//mBeatMaxTime   = pTimeStamp + ( pWindowSize / 2 );
			mBeatMaxTime   = pTimeStamp;
			mBeatSamples   = 0;
			mInBeat        = true;
			mBeatAscending = true;
			mBeatLastValue = pValue;
			mBeatStartTime = pTimeStamp;
		}
		else
		{
			if( pValue > mBeatMax )
			{
				mBeatMax     = pValue;
				//mBeatMaxTime = pTimeStamp + ( pWindowSize / 2 );
			}

			if( pValue - pAverage > mBeatRelMax )
			{
				mBeatRelMax  = pValue - pAverage;
				//mBeatMaxTime = pTimeStamp;
			}
		}

		mBeatSamples++;
	}
	else if( mInBeat )
	{
		addBeat( mBeatMaxTime, mBeatRelMax );

		mInBeat = false;
	}
}

bool AnalysisBeat::processTime( PtTimestamp pTimeStamp )
{
	mAnalysisTempo.processTime( pTimeStamp, mBeatOffset );

	mCalcBpm             = mAnalysisTempo.getCurrentBpm();
	//mCalcTempoConfidence = mAnalysisTempo.getTempoConfidence();
	mCalcSyncConfidence  = mAnalysisTempo.getSyncConfidence();

	if( mAnalysisTempo.isBeat() )
	{
		mBeat = ( mBeat + 1 ) % 4;

		mIsBeat = true;
	}

	return( mIsBeat );
}

void AnalysisBeat::addBeat( DWORD pTime, float pPower )
{
//	wxCriticalSectionLocker		Lock( mBeatLock );

	BeatEntry		Entry;

	Entry.mTimeStamp = pTime;
	Entry.mPower     = pPower;

	mBeats.push_back( Entry );

	mBeatsAdded++;

	mAnalysisTempo.processImpulse( pTime, pPower, mBeatLocked );
}

void AnalysisBeat::setBeat( void )
{
	mBeat = 0;

	mAnalysisTempo.setBeat( timeGetTime() );
}

void AnalysisBeat::processBeats( void )
{
	PtTimestamp		Now = timeGetTime();
	size_t			BeatCount;

	while( ( BeatCount = mBeats.size() ) > 0 && ( BeatCount > 100 || Now - mBeats.front().mTimeStamp >= 10000 ) )
	{
		mBeats.erase( mBeats.begin() );
	}

	if( mBeatsAdded == 0 )
	{
		return;
	}

	mBeatsAdded = 0;

	memset( mBpmMap, 0, sizeof( float ) * COUNT_VALUES );

	for( vector<BeatEntry>::iterator it1 = mBeats.begin() ; it1 != mBeats.end() ; it1++ )
	{
		BeatEntry	e1 = *it1;
		
		for( vector<BeatEntry>::iterator it2 = it1 + 1 ; it2 != mBeats.end() ; it2++ )
		{
			BeatEntry	e2 = *it2;

			if( e2.mTimeStamp == e1.mTimeStamp )
			{
				continue;
			}

			for( float Beat = 1.0 ; Beat < 64.0 ; Beat += 1.0 )
			{
				const float		BeatLen = (float)( e2.mTimeStamp - e1.mTimeStamp ) / Beat;
				const float		BeatBpm = 60000.0 / BeatLen;

				if( BeatBpm < BPM_SCAN_MIN )
				{
					continue;
				}

				if( BeatBpm > BPM_SCAN_MAX )
				{
					break;
				}

				const UINT		BPM_FLOOR = (UINT)floor( BeatBpm );
				const UINT		BPM_CEIL  = (UINT)ceil( BeatBpm );
				const float		BPM_RATIO = BeatBpm - (float)BPM_FLOOR;

				if( BPM_FLOOR < BPM_SCAN_MIN )
				{
					continue;
				}

				if( BPM_CEIL > BPM_SCAN_MAX )
				{
					break;
				}

				const float		Power = ( e1.mPower + e2.mPower ) / 2.0;

				mBpmMap[ BPM_FLOOR ] += Power * ( 1.0 - BPM_RATIO );
				mBpmMap[ BPM_CEIL ]  += Power * BPM_RATIO;
			}
		}
	}

	//-------------------------------------------------------------------------

	float		MaxBpmMap = 0.0;

	for( int i = 0 ; i < COUNT_VALUES ; i++ )
	{
		if( mBpmMap[ i ] > MaxBpmMap )
		{
			MaxBpmMap = mBpmMap[ i ];

			mBpm = i;
		}
	}

	//-------------------------------------------------------------------------

	if( true )
	{
		float		BpmMapSum = 0.0;
		float		BpmMapAmt = 0.0;

		for( int i = -1 ; i <= 1 ; i++ )
		{
			BpmMapSum += mBpmMap[ (int)mBpm + i ] * (float)( mBpm + i );
			BpmMapAmt += mBpmMap[ (int)mBpm + i ];
		}

		if( BpmMapSum > 0.0 )
		{
			mBpm = BpmMapSum / BpmMapAmt;
		}
	}

	while( mBpm > mBpmMax ) mBpm /= 2.0;
	while( mBpm < mBpmMin ) mBpm *= 2.0;

	//-------------------------------------------------------------------------

	if( MaxBpmMap > 1.0 )
	{
		for( int i = 0 ; i < COUNT_VALUES ; i++ )
		{
			mBpmMap[ i ] /= MaxBpmMap;
		}
	}
	
	//-------------------------------------------------------------------------

	float		BpmMapSum = 0.0;
	float		BpmMapCnt = 0.0;

	for( int i = BPM_SCAN_MIN ; i < BPM_SCAN_MAX ; i++ )
	{
		BpmMapSum += mBpmMap[ i ];
		BpmMapCnt += 1.0;
	}

	const float		BpmMapAvg = BpmMapSum / BpmMapCnt;

	//-------------------------------------------------------------------------

	if( fabs( mBpm - mBpmCur ) < 3 )
	{
		mBpmCur    = ( mBpm + mBpmCur ) / 2.0;
		mBpmCurCnt = min( mBpmCurCnt + 1, BPM_MAX_CNT );

		for( int i = 0 ; i < BPM_NEW_CNT ; i++ )
		{
			mBpmNewCnt[ i ] = max( mBpmNewCnt[ i ] - 1, 0 );
		}
	}
	else if( fabs( ( mBpm * 2.0 ) - mBpmCur ) < 3 || fabs( ( mBpm / 2.0 ) - mBpmCur ) < 3 )
	{
		mBpmCurCnt = min( mBpmCurCnt + 1, BPM_MAX_CNT );

		for( int i = 0 ; i < BPM_NEW_CNT ; i++ )
		{
			mBpmNewCnt[ i ] = max( mBpmNewCnt[ i ] - 1, 0 );
		}
	}
	else if( mBeatLocked )
	{
		mBpmCurCnt = max( mBpmCurCnt - 1, 0 );
	}
	else
	{
		int		FoundIdx = -1;

		for( int i = 0 ; i < BPM_NEW_CNT ; i++ )
		{
			if( fabs( mBpm - mBpmNew[ i ] ) < 3 )
			{
				mBpmNew[ i ]    = ( mBpm + mBpmNew[ i ] ) / 2.0;
				mBpmNewCnt[ i ] = min( mBpmNewCnt[ i ] + 1, BPM_MAX_CNT );

				FoundIdx = i;
			}
			else
			{
				mBpmNewCnt[ i ] = max( mBpmNewCnt[ i ] - 1, 0 );
			}
		}

		if( FoundIdx == -1 )
		{
			for( int i = 0 ; i < BPM_NEW_CNT ; i++ )
			{
				if( mBpmNewCnt[ i ] == 0 )
				{
					mBpmNew[ i ] = mBpm;

					FoundIdx = i;

					break;
				}
			}
		}

		mBpmCurCnt = max( mBpmCurCnt - 1, 0 );

		if( FoundIdx != -1 && mBpmNewCnt[ FoundIdx ] >= mBpmCurCnt )
		{
			float		BpmTmp = mBpmCur;
			int			CntTmp = mBpmCurCnt;

			mBpmCur = mBpmNew[ FoundIdx ];
			mBpmCurCnt = mBpmNewCnt[ FoundIdx ];
			mBpmNew[ FoundIdx ] = BpmTmp;
			mBpmNewCnt[ FoundIdx ] = CntTmp;
		}
	}

	mBpm = mBpmCur;
/*
	wxString		Out = wxString::Format( _( "CUR: %3.2f (%d) - NEW:" ), mBpmCur, mBpmCurCnt );

	for( int i = 0 ; i < BPM_NEW_CNT ; i++ )
	{
		Out += wxString::Format( _( " %3.2f (%d)" ), mBpmNew[ i ], mBpmNewCnt[ i ] );
	}

	wxLogDebug( Out );
*/
	//mCalcTempoConfidence = min( 1.0, ( ( 1.0 - ( BpmMapSum / BpmMapCnt ) ) - 0.2 ) * 1.25 );

	//mCalcTempoConfidence = min( MaxBpmMap, 1.0 ) - ( BpmMapSum / BpmMapCnt );
/*
	int		MaxBpmCnt = 0;

	for( int i = 0 ; i < BPM_NEW_CNT ; i++ )
	{
		if( mBpmNewCnt[ i ] > MaxBpmCnt )
		{
			MaxBpmCnt = mBpmNewCnt[ i ];
		}
	}
*/
	mCalcTempoConfidence = (float)mBpmCurCnt / (float)BPM_MAX_CNT;

	if( mBpm == 0.0 )
	{
		return;
	}

	mBeatLength = (DWORD)( 60000.0 / mBpm );

	mAnalysisTempo.processTempo( 60000.0 / mBpm, mCalcTempoConfidence );

	mLastTime = Now;
	mLastBpm  = mBpm;
}
