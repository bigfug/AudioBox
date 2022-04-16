#pragma once

#include "Analysis.h"
#include "FFT.h"
#include "AudioWindow.h"
#include "Average.h"

class AnalysisFFT : public Analysis
{
protected:
	USE_FFT				*mFFT;
	AudioWindow			*mWindowFunction;
	float				 mSpectralCentroid;
	AverageFloat		*mSpectralCentroidAverage;
	float				 mHFC;
	AverageFloat		*mHFCAverage;
public:
	AnalysisFFT( void );

	virtual ~AnalysisFFT( void );

	bool initialise( const int pSampleRate, const int pSamplesPerFrame );

	void deinitialise( void );

	void processData( const float *pInputLeft, const float *pInputRight, const float *pInputMono );

	inline FFT *getFFT( void ) const
	{
		return( mFFT );
	}

	inline float getSpectralCentroid( void ) const
	{
		return( mSpectralCentroid );
	}

	inline AverageFloat &getSpectralCentroidAverage( void ) const
	{
		return( *mSpectralCentroidAverage );
	}

	inline float getHFC( void ) const
	{
		return( mHFC );
	}

	inline AverageFloat &getHFCAverage( void ) const
	{
		return( *mHFCAverage );
	}
};
