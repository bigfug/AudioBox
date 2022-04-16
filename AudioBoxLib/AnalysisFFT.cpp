#include "StdAfx.h"
#include "AnalysisFFT.h"

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

AnalysisFFT::AnalysisFFT( void )
: mHFCAverage( 0 ), mSpectralCentroidAverage( 0 ), mWindowFunction( 0 ), mFFT( 0 )
{
}

AnalysisFFT::~AnalysisFFT( void )
{
	deinitialise();
}

bool AnalysisFFT::initialise( const int pSampleRate, const int pSamplesPerFrame )
{
	Analysis::initialise( pSampleRate, pSamplesPerFrame );

	mFFT = new USE_FFT( mSamplesPerFrame );

	mWindowFunction = new AudioWindow( WINDOW_HANNING, mSamplesPerFrame );

	mSpectralCentroid = 0.0f;
	mSpectralCentroidAverage = new AverageFloat( ( mSampleRate / mSamplesPerFrame ) * 2 );

	mHFC = 0.0f;
	mHFCAverage = new AverageFloat( ( mSampleRate / mSamplesPerFrame ) * 2 );

	return( true );
}

void AnalysisFFT::deinitialise( void )
{
	SAFE_DELETE( mHFCAverage );

	SAFE_DELETE( mSpectralCentroidAverage );

	SAFE_DELETE( mWindowFunction );

	SAFE_DELETE( mFFT );

	Analysis::deinitialise();
}

void AnalysisFFT::processData( const float *pInputLeft, const float *pInputRight, const float *pInputMono )
{
	const double	 FreqPerBin = ( (double)mSampleRate / 2.0 ) / ( (double)mSamplesPerFrame / 2.0 );
	float			*DataPtr = mFFT->getOutputBuffer();
	double			 Frequency;
	double			 SpectralTotal;
	double			 SpectralDivider;

	//---------------------------------------------------------------------
	// Process the FFT

	mWindowFunction->ProcessWindow( pInputMono, mFFT->getInputBuffer() );

	mFFT->PowerSpectrum();
/*
	for( int i = 0 ; i < mSamplesPerFrame / 2 ; i++ )
	{
		DataPtr[ i ] = ( log10( DataPtr[ i ] + 1.0f ) ) / 6.0f;
	}
*/
	//---------------------------------------------------------------------
	// Calculate the spectral centroid

	DataPtr = mFFT->getOutputBuffer();

	SpectralTotal = SpectralDivider = 0.0;
	
	for( int i = 0 ; i < mSamplesPerFrame / 2 ; i++ )
	{
		SpectralTotal   += ( (double)( i + 1 ) * FreqPerBin ) * (double)DataPtr[ i ];
		
		SpectralDivider += (double)DataPtr[ i ];
	}

	mSpectralCentroid = (float)( ( SpectralTotal / SpectralDivider ) / ( (double)mSampleRate / 2.0 ) );

	mSpectralCentroidAverage->addValue( mSpectralCentroid );

	//---------------------------------------------------------------------
	// Calculate HFC

	DataPtr = mFFT->getOutputBuffer();

	for( int i = 0 ; i < mSamplesPerFrame / 2 ; i++ )
	{
		float		tmp = i > 0 ? (float)i / (float)i : 0;

		mHFC += ( DataPtr[ i ] * ( tmp * tmp ) ) / 0.5f;
	}

	mHFC /= (float)mSamplesPerFrame / 2.0f;
	
	if( mHFC > 1.0f ) mHFC = 1.0f;

	mHFCAverage->addValue( mHFC );
}
