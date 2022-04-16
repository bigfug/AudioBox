#pragma once

#include "Analysis.h"
#include "Average.h"

class AnalysisWave : public Analysis
{
protected:
	AverageFloat		*mAutoGainAverage;
	float				 mAmplitude;
	AverageFloat		*mAmplitudeAverage;
	float				*mAmplifiedInput;
	float				 mGain;

	float				 mAmplitudeLeft;
	AverageFloat		*mAmplitudeAverageLeft;
	float				*mAmplifiedInputLeft;

	float				 mAmplitudeRight;
	AverageFloat		*mAmplitudeAverageRight;
	float				*mAmplifiedInputRight;
public:
	AnalysisWave( void );

	virtual ~AnalysisWave( void );

	bool initialise( const int pSampleRate, const int pSamplesPerFrame );

	void deinitialise( void );

	void processData( const float *pInputLeft, const float *pInputRight, const float *pInputMono );

	inline float getAmplitudeLeft( void ) const
	{
		return( mAmplitudeLeft );
	}

	inline const AverageFloat &getAmplitudeAverageLeft( void ) const
	{
		return( *mAmplitudeAverageLeft );
	}

	inline float getAmplitudeRight( void ) const
	{
		return( mAmplitudeRight );
	}

	inline const AverageFloat &getAutoGainAverage( void ) const
	{
		return( *mAutoGainAverage );
	}

	inline const float *getAmplifiedInput( void ) const
	{
		return( mAmplifiedInput );
	}

	inline float getGain( void ) const
	{
		return( mGain );
	}
};
