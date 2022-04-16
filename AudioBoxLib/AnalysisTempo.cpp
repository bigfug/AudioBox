
#include "StdAfx.h"
#include "AnalysisTempo.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

AnalysisTempo::AnalysisTempo( void )
: mImpulsePowerAverage( 30 ), mBeatAdjustAverage( 30 )
{
}

AnalysisTempo::~AnalysisTempo( void )
{
	deinitialise();
}

bool AnalysisTempo::initialise( const int pSampleRate, const int pSamplesPerFrame )
{
	Analysis::initialise( pSampleRate, pSamplesPerFrame );

	mStartBPM = mBPM = 120.0;

	mBeatLength = 60000.0f / mBPM;
	mBeatMargin = mBeatLength / 8.0f;
	
	mLastBeat  = timeGetTime();
	mNextBeat  = mLastBeat + mBeatLength;
	mNextBeat2 = mNextBeat + mBeatLength;

	mSyncConfidence = 0.0;

	mIsBeat = false;

	mImpulsePowerAverage.reset();

	mBeatAdjustAverage.reset();

	memset( mBeatMap, 0, sizeof( UINT ) * 17 );

	mLastBeatMapOffset = 0;

	memset( mBeatOffset, 0, sizeof( float ) * 1024 );

	return( true );
}

void AnalysisTempo::deinitialise( void )
{
	Analysis::deinitialise();
}

void AnalysisTempo::processImpulse( const PtTimestamp pTimeStamp, const float pPower, const bool pLocked )
{
	const double		BeatTimeOffset = (double)pTimeStamp - mLastBeat;
	const int			BeatSemiOffset = (int)( BeatTimeOffset / ( mBeatLength / 4 ) );
	const double		BeatSemiTarget = ( (double)BeatSemiOffset * ( mBeatLength / 4 ) );
	const double		BeatSemiAdjust = BeatSemiTarget - BeatTimeOffset;

	mImpulsePowerAverage.addValue( pPower );

	if( pPower >= mImpulsePowerAverage.getAverage() && fabs( BeatSemiAdjust ) < mBeatLength / 8 )
	{
		mBeatAdjustAverage.addValue( BeatSemiAdjust );

		static int			BeatAdjustCounter = 0;

		if( ++BeatAdjustCounter == 16 )
		{
			//wxLogDebug( _( "ADJ: %f" ), mBeatAdjustAverage.getAverage() );

			//mNextBeat2 += mBeatAdjustAverage.getAverage();

			mBeatAdjustAverage.reset();

			BeatAdjustCounter = 0;
		}
	}

	const UINT			BeatMapEntry = 8 + ( BeatSemiOffset % 8 );

	//wxLogDebug( _( "SYNC BEAT: %+d - ADJ: %f - AVG: %f" ), BeatSemiOffset, BeatSemiAdjust, mBeatAdjustAverage.getAverage() );

	for( int i = 0 ; i < 17 ; i++ )
	{
		if( i == BeatMapEntry )
		{
			mBeatMap[ i ] = min( mBeatMap[ i ] + 1, 999 );
		}
		else
		{
			//mBeatMap[ i ] = max( mBeatMap[ i ] - 1, 0 );
		}

		//if( mBeatMap[ i ] >= 4 )
		//{
		//	const int		Offset = i - 8;

		//	if( Offset == mLastBeatMapOffset )
		//	{
		//		wxLogDebug( _( "OFFSET %+d = %f" ), i - 8, ( mBeatLength / 8 ) * ( Offset ) );

		//		if( !pLocked )
		//		{
		//			mNextBeat2 += ( mBeatLength / 8 ) * ( mLastBeatMapOffset );
		//		}

		//		mLastBeatMapOffset = 0;
		//	}
		//	else
		//	{
		//		mLastBeatMapOffset = Offset;
		//	}

		//	memset( mBeatMap, 0, sizeof( UINT ) * 17 );

		//	break;
		//}
	}

	//wxString		Out;

	//for( int i = 0 ; i < 17 ; i++ )
	//{
	//	if( i == 8 )
	//	{
	//		Out += wxString::Format( _( " - %03d -" ), mBeatMap[ i ] );
	//	}
	//	else
	//	{
	//		Out += wxString::Format( _( " %3d" ), mBeatMap[ i ] );
	//	}
	//}

	//wxLogDebug( _( "BEATMAP:" ) + Out );

	const int		BeatOffsetEntry = ( BeatTimeOffset / 4 ) + 512;

	if( BeatOffsetEntry < 0 || BeatOffsetEntry >= 1024 )
	{
		return;
	}

	mBeatOffset[ BeatOffsetEntry ] += pPower;

	static DWORD		LastUpdate = 0;
	DWORD				Now = timeGetTime();

	if( Now - LastUpdate > 10000 )
	{
		LastUpdate = Now;

		float		MaxOffset = 0.0;
		float		MinOffset = 16384.0;
		int			MaxIndex  = 0;

		for( int i = 0 ; i < 1024 ; i++ )
		{
			if( mBeatOffset[ i ] > MaxOffset )
			{
				MaxOffset = mBeatOffset[ i ];
				MaxIndex  = i;
			}
		}

		const int		Offset  = ( MaxIndex - 512 ) * 4;
		const int		HalfOff = (int)( mBeatLength / 2.0 );

		static int		LastOffset = 0;
		static int		LastCount  = 0;

		//if( LastOffset == Offset )
		if( MaxOffset >= 1.0 )
		{
			//if( ++LastCount > 50 )
			{
				if( abs( abs( Offset ) - HalfOff ) < abs( Offset ) )
				{
					const int	NewOff = Offset - ( Offset > 0 ? HalfOff : -HalfOff );
					const int	NewIdx = ( NewOff / 4 ) + 512;

					wxLogDebug( _( "OFFSET HALF: %d (%d,%d) (%f - %f)" ), Offset, NewOff, NewIdx, mBeatOffset[ MaxIndex ], mBeatOffset[ NewIdx ] );

					if( abs( NewOff ) <= HalfOff )
					{
						mNextBeat2 += NewOff;
					}
				}
				else
				{
					wxLogDebug( _( "OFFSET: %d (%f)" ), Offset, mBeatOffset[ MaxIndex ] );

					if( abs( Offset ) <= HalfOff )
					{
						mNextBeat2 += Offset;
					}
				}

				LastOffset = 0;
				LastCount  = 0;

				memset( mBeatOffset, 0, sizeof( float ) * 1024 );
			}
		}
		//else
		//{
		//	LastOffset = Offset;
		//	LastCount  = 0;
		//}
	}
}

void AnalysisTempo::processTempo( const float pBeatLength, const float pConfidence )
{
#if 0
	if( pConfidence >= 0.2 )
	{
		mBeatLengthAverage.addValue( pBeatLength );

		mBeatLength = mBeatLengthAverage.getAverageMode();

		mBPM = 60000.0 / mBeatLength;
	}
#endif

	if( fabs( ( 60000.0 / mBeatLength ) - ( 60000.0 / pBeatLength ) ) > 3.0 )
	{
		memset( mBeatMap, 0, sizeof( UINT ) * 17 );
		memset( mBeatOffset, 0, sizeof( float ) * 1024 );
	}

	mBeatLength = pBeatLength;

	mBPM = 60000.0 / mBeatLength;
}

void AnalysisTempo::setBeat( const PtTimestamp pTimeStamp )
{
	mIsBeat   = true;
		
	mLastBeat  = pTimeStamp;
	mNextBeat  = mLastBeat + mBeatLength;
	mNextBeat2 = mNextBeat + mBeatLength;

	memset( mBeatOffset, 0, sizeof( float ) * 1024 );

	mBeatPhase = 1.0f;
}

void AnalysisTempo::processTime( const PtTimestamp pTimeStamp, float &pBeatOffset )
{
	mIsBeat = false;
	
	if( mNextBeat > 0 && pTimeStamp >= mNextBeat )
	{
		mIsBeat   = true;
		
		mLastBeat  = mNextBeat;
		mNextBeat  = mNextBeat2;
		mNextBeat2 = mNextBeat + mBeatLength + ( mBeatLength * (double)pBeatOffset );

		if( pBeatOffset != 0 )
		{
			memset( mBeatOffset, 0, sizeof( float ) * 1024 );
		}

		pBeatOffset = 0.0;

		mBeatPhase = 1.0f;
	}
	else
	{
		mBeatPhase = 1.0f - ( max( (double)pTimeStamp - mLastBeat, 1.0 ) / ( mNextBeat - mLastBeat ) );
	}

	//mBeatLengthAverage.addValue( mBeatLengthAverage.getLastValue() );
}

