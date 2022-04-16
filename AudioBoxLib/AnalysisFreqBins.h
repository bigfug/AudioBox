#pragma once

#include "Analysis.h"
#include "FFT.h"
#include "Average.h"

class AnalysisFreqBins : public Analysis
{
protected:
	AverageFloat		*mBandAvg[ 16 ];
	AverageFloat		*mVarianceAvg[ 16 ];
	AverageFloat		*mBandAvgTotal;
	AverageFloat		*mBandAvgTotalMax;
public:
	AnalysisFreqBins( void );

	virtual ~AnalysisFreqBins(void);

	bool initialise( const int pSampleRate, const int pSamplesPerFrame );

	void deinitialise( void );

	void processData( FFT *pFFT, float *pEq );

	void processDataEq( FFT *pFFT, float *pEq );

	float getBeatAvg( void ) const
	{
		return( mBandAvgTotal->getLastValue() );
	}

	float getBeatAvgTotal( void ) const
	{
//		return( mBandAvgTotal->getAverage() + ( ( mBandAvgTotalMax->getAverage() - mBandAvgTotal->getAverage() ) / 2.0f ) );

		return( mBandAvgTotal->getAverage() );
	}

	AverageFloat **getBandAvg( void )
	{
		return( mBandAvg );
	}

	AverageFloat **getVarianceAvg( void )
	{
		return( mVarianceAvg );
	}
};
