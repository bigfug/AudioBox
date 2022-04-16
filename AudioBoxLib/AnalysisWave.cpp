#include "StdAfx.h"
#include "AnalysisWave.h"

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

AnalysisWave::AnalysisWave( void )
: mAutoGainAverage( 0 ), mAmplitudeAverage( 0 ), mAmplifiedInput( 0 ),
  mAmplitudeAverageLeft( 0 ), mAmplifiedInputLeft( 0 ),
  mAmplitudeAverageRight( 0 ), mAmplifiedInputRight( 0 )
{
}

AnalysisWave::~AnalysisWave( void )
{
}

bool AnalysisWave::initialise( const int pSampleRate, const int pSamplesPerFrame )
{
	Analysis::initialise( pSampleRate, pSamplesPerFrame );

	mAmplitude				= 0.0;
	mAutoGainAverage		= new AverageFloat( ( mSampleRate / mSamplesPerFrame ) * 4 );
	mAmplitudeAverage		= new AverageFloat( ( mSampleRate / mSamplesPerFrame ) * 2 );
	mAmplifiedInput			= new float[ pSamplesPerFrame ];

	mAmplitudeLeft			= 0.0f;
	mAmplitudeAverageLeft	= new AverageFloat( ( mSampleRate / mSamplesPerFrame ) * 2 );
	mAmplifiedInputLeft		= new float[ pSamplesPerFrame ];
	
	mAmplitudeRight			= 0.0f;
	mAmplitudeAverageRight	= new AverageFloat( ( mSampleRate / mSamplesPerFrame ) * 2 );
	mAmplifiedInputRight	= new float[ pSamplesPerFrame ];

	return( true );
}

void AnalysisWave::deinitialise( void )
{
	SAFE_DELETE( mAmplitudeAverageLeft );
	SAFE_DELETE_ARRAY( mAmplifiedInputLeft );

	SAFE_DELETE( mAmplitudeAverageRight );
	SAFE_DELETE_ARRAY( mAmplifiedInputRight );

	SAFE_DELETE( mAutoGainAverage );
	SAFE_DELETE( mAmplitudeAverage );
	SAFE_DELETE_ARRAY( mAmplifiedInput );

	Analysis::deinitialise();
}

void AnalysisWave::processData( const float *pInputLeft, const float *pInputRight, const float *pInputMono )
{
	int			 i;

	if( pInputMono != 0 )
	{
		float		 InputMin, InputMax;

		//---------------------------------------------------------------------
		// Calculate the amplitude of the input signal

		InputMin = InputMax = 0.0f;

		for( i = 0 ; i < mSamplesPerFrame ; i++ )
		{
			if( pInputMono[ i ] < InputMin ) InputMin = pInputMono[ i ];

			if( pInputMono[ i ] > InputMax ) InputMax = pInputMono[ i ];
		}

		mAmplitude = fabs( InputMax - InputMin ) / 2.0f;

		mAmplitudeAverage->addValue( mAmplitude );

		//---------------------------------------------------------------------
		// Calculate the auto gain

		mAutoGainAverage->addValue( max( 0.80f - mAmplitude, 0.0f ) );

		if( mAmplitude > 0 && mAutoGainAverage->getAverage() > 0.1f && mAutoGainAverage->getAverage() < 1.0f )
		{
			mGain = 1.0f + mAutoGainAverage->getAverage();

			for( i = 0 ; i < mSamplesPerFrame ; i++ )
			{
				mAmplifiedInput[ i ] = pInputMono[ i ] * mGain;
			}
		}
		else
		{
			mGain = 1.0;

			memcpy( mAmplifiedInput, pInputMono, mSamplesPerFrame * sizeof( float ) );
		}
	}
	else
	{
		float		 MinL, MaxL, MinR, MaxR;

		MinL = MaxL = MinR = MaxR = 0.0;

		//---------------------------------------------------------------------
		// Calculate the amplitude of the input signal

		for( i = 0 ; i < mSamplesPerFrame ; i++ )
		{
			if( pInputLeft[ i ] < MinL ) MinL = pInputLeft[ i ];

			if( pInputLeft[ i ] > MaxL ) MaxL = pInputLeft[ i ];

			if( pInputRight[ i ] < MinR ) MinR = pInputRight[ i ];

			if( pInputRight[ i ] > MaxR ) MaxR = pInputRight[ i ];
		}

		mAmplitudeLeft  = fabs( MaxL - MinL ) / 2.0f;
		mAmplitudeRight = fabs( MaxR - MinR ) / 2.0f;

		mAmplitude = max( mAmplitudeLeft, mAmplitudeRight );

		mAmplitudeAverage->addValue( mAmplitude );

		//---------------------------------------------------------------------
		// Calculate the auto gain

		mAutoGainAverage->addValue( max( 0.80f - mAmplitude, 0.0f ) );

		if( mAmplitude > 0 && mAutoGainAverage->getAverage() > 0.1f && mAutoGainAverage->getAverage() < 1.0f )
		{
			mGain = 1.0f + mAutoGainAverage->getAverage();

			for( i = 0 ; i < mSamplesPerFrame ; i++ )
			{
				mAmplifiedInputLeft[ i ]  = pInputLeft[ i ] * mGain;
				mAmplifiedInputRight[ i ] = pInputRight[ i ] * mGain;
				mAmplifiedInput[ i ] = ( mAmplifiedInputLeft[ i ] + mAmplifiedInputRight[ i ] ) / 2.0;
			}
		}
		else
		{
			mGain = 1.0;

			memcpy( mAmplifiedInputLeft, pInputLeft, mSamplesPerFrame * sizeof( float ) );
			memcpy( mAmplifiedInputRight, pInputRight, mSamplesPerFrame * sizeof( float ) );

			for( i = 0 ; i < mSamplesPerFrame ; i++ )
			{
				mAmplifiedInput[ i ] = ( mAmplifiedInputLeft[ i ] + mAmplifiedInputRight[ i ] ) / 2.0;
			}
		}
	}
}

//void AnalysisWave::getAmplitude( const float *pInputLeft, const float *pInputRight, const float *pInputMono )
//{
//}
