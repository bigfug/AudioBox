#include "StdAfx.h"
#include "AnalysisFreqBins.h"

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

AnalysisFreqBins::AnalysisFreqBins( void )
: mBandAvgTotal( 0 ), mBandAvgTotalMax( 0 )
{
	for( int i = 0 ; i < 16 ; i++ )
	{
		mBandAvg[ i ] = 0;
	
		mVarianceAvg[ i ] = 0;
	}
}

AnalysisFreqBins::~AnalysisFreqBins( void )
{
	deinitialise();
}

bool AnalysisFreqBins::initialise( const int pSampleRate, const int pSamplesPerFrame )
{
	Analysis::initialise( pSampleRate, pSamplesPerFrame );

	for( int i = 0 ; i < 16 ; i++ )
	{
		mBandAvg[ i ] = new AverageFloat( 32 );

		mVarianceAvg[ i ] = new AverageFloat( 256 );
	}

	mBandAvgTotal    = new AverageFloat( ( pSampleRate / pSamplesPerFrame ) * 8 );
	mBandAvgTotalMax = new AverageFloat( ( pSampleRate / pSamplesPerFrame ) * 8 );

	return( true );
}

void AnalysisFreqBins::deinitialise( void )
{
	SAFE_DELETE( mBandAvgTotal );
	SAFE_DELETE( mBandAvgTotalMax );

	for( int i = 0 ; i < 16 ; i++ )
	{
		SAFE_DELETE( mBandAvg[ i ] );
		SAFE_DELETE( mVarianceAvg[ i ] );
	}

	Analysis::deinitialise();
}

void AnalysisFreqBins::processData( FFT *pFFT, float *pEq )
{
	const float		*Spectrum    = pFFT->getOutputBuffer();
	const float		 HighFreqPos = ( 44100.0f / mSampleRate ) * (float)( mSamplesPerFrame / 2 );
	const int		 MaxPoint    = min( mSamplesPerFrame / 2, (int)HighFreqPos );
	int				 Start, Count;
	float			 Temp, Total, Max, Min, BinCount;

	Start = 0;
	Total = 0.0f;
	BinCount = 0.0;
	Max = -1.0f;
	Min =  1.0f;

	for( int i = 0 ; i < 16 ; i++ )
	{
		const int End  = (int)( ( 1.0f - log10( ( ( (float)( 15 - i ) / 16.0f ) * 9 ) + 1 ) ) * (float)MaxPoint );
		//const int End  = ( ( ( i + 1 ) * MaxPoint ) / 16 ) - 1;

		Count = 0;
		Temp  = 0.0f;

		for( int j = Start ; j < End ; j++ )
		{
			Temp += Spectrum[ j ];

			Count++;
		}

		mBandAvg[ i ]->addValue( ( Temp / (float)Count ) * pEq[ i ] );
/*
		const float		BandDiff    = mBandAvg[ i ]->getMax() - mBandAvg[ i ]->getMin();
		const float		BandMaxDiff = mBandAvg[ i ]->getMax() - mBandAvg[ i ]->getAverage();
		const float		BandMinDiff = mBandAvg[ i ]->getAverage() - mBandAvg[ i ]->getMin();

		if( BandDiff > 0.0 )
		{
			mVarianceAvg[ i ]->addValue( ( ( BandMaxDiff / BandDiff ) - ( BandMinDiff / BandDiff ) ) + 0.5 );
		}
		else
		{
			mVarianceAvg[ i ]->addValue( 0.5 );
		}
*/
		Temp = mBandAvg[ i ]->getLastValue() - mBandAvg[ i ]->getAverage();

		if( Temp > Max )
		{
			Max = Temp;
		}

		if( Temp < Min )
		{
			Min = Temp;
		}

		if( Temp > 0.0 )
		{
			Total += Temp;

			BinCount += pEq[ i ];
		}

		Start = End + 1;
	}

	if( BinCount > 0.0 )
	{
		Total /= BinCount;
	}
	else
	{
		Total = 0.0f;
	}

	//mBandAvgTotal->addValue( Total + 0.5f );

	mBandAvgTotal->addValue( Total * 2.0 );

	mBandAvgTotalMax->addValue( mBandAvgTotal->getMax() );
}

void AnalysisFreqBins::processDataEq( FFT *pFFT, float *pEq )
{
	const float		*Spectrum    = pFFT->getOutputBuffer();
	const float		 HighFreqPos = ( 44100.0f / mSampleRate ) * (float)( mSamplesPerFrame / 2 );
	const int		 MaxPoint    = min( mSamplesPerFrame / 2, (int)HighFreqPos );
	int				 Start, Count;
	float			 Temp, Total, Max, Min, BinCount;

	Start = 0;
	Total = 0.0f;
	BinCount = 0.0;
	Max = -1.0f;
	Min =  1.0f;

	for( int i = 0 ; i < 16 ; i++ )
	{
		const int End  = (int)( ( 1.0f - log10( ( ( (float)( 15 - i ) / 16.0f ) * 9 ) + 1 ) ) * (float)MaxPoint );
		//const int End  = ( ( ( i + 1 ) * MaxPoint ) / 16 ) - 1;

		Count = 0;
		Temp  = 0.0f;

		for( int j = Start ; j < End ; j++ )
		{
			Temp += Spectrum[ j ];

			Count++;
		}

		mBandAvg[ i ]->addValue( Temp / (float)Count );

		const float		BandDiff    = mBandAvg[ i ]->getMax() - mBandAvg[ i ]->getMin();
		const float		BandMaxDiff = mBandAvg[ i ]->getMax() - mBandAvg[ i ]->getAverage();
		const float		BandMinDiff = mBandAvg[ i ]->getAverage() - mBandAvg[ i ]->getMin();

		if( BandDiff > 0.0 )
		{
			mVarianceAvg[ i ]->addValue( ( ( BandMaxDiff / BandDiff ) - ( BandMinDiff / BandDiff ) ) + 0.5 );
		}
		else
		{
			mVarianceAvg[ i ]->addValue( 0.5 );
		}

		pEq[ i ] = mVarianceAvg[ i ]->getAverage();

		Start = End + 1;
	}
}
