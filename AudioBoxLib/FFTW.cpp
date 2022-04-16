#include "stdafx.h"
#include ".\fft.h"
#include "fftw3.h"

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

#define IS_FFTW

FFT_FFTW::FFT_FFTW( const int pNumSamples )
: FFT( pNumSamples ), mNumSamples( pNumSamples ), mMaxVal( 0.0 )
{
	mInput  = (float *)fftwf_malloc( sizeof( float ) * mNumSamples );
	mOutput = (float *)fftwf_malloc( sizeof( float ) * max( mNumSamples, 1024 ) );
	mScale  = (float *)fftwf_malloc( sizeof( float ) * mNumSamples );

	mPlan = fftwf_plan_r2r_1d( pNumSamples, mInput, mOutput, FFTW_R2HC, FFTW_PATIENT );
}

FFT_FFTW::~FFT_FFTW(void)
{
	fftwf_destroy_plan( mPlan );

	fftwf_free( mInput );
	fftwf_free( mOutput );
	fftwf_free( mScale );
}

void FFT_FFTW::PowerSpectrum( void )
{
	fftwf_execute( mPlan );

	/*
	 * Phase spectrum
	 * FFT originally works with complex data. The output is therefore also complex.
	 * The amplitude of the signal is calculated as:
	 *
	 * Amplt2 = Im2 + Re2
	 *
	 * And the phase analogue:
	 *
	 * Phase = arctang (Im/Re)
	 */

	mOutput[ 0 ] = ( mOutput[ 0 ] * mOutput[ 0 ] );  // DC component

	for( int i = 1 ; i < ( mNumSamples + 1 ) / 2 ; i++ )  // (k < N/2 rounded up)
	{
		mOutput[ i ] = ( mOutput[ i ] * mOutput[ i ] ) + ( mOutput[ mNumSamples - i ] * mOutput[ mNumSamples - i ] );
	}

	if( mNumSamples % 2 == 0 ) // N is even
	{
		mOutput[ mNumSamples / 2 ] = ( mOutput[ mNumSamples / 2 ] * mOutput[ mNumSamples / 2 ] );  // Nyquist freq.
	}

	for( int i = 0 ; i < mNumSamples ; i++ )
	{
		mOutput[ i ] = 10.0 * log10( 1.0 + mOutput[ i ] );

		if( i > mNumSamples / 2 )
		{
			mOutput[ i ] = 0.0;
		}
		else
		{
			if( mOutput[ i ] > mScale[ i ] )
			{
				mScale[ i ] = mOutput[ i ];
			}

			mOutput[ i ] /= mScale[ i ];
		}
	}
/*
	if( mMaxVal > 1.0 )
	{
		for( int i = 0 ; i < mNumSamples ; i++ )
		{
			mOutput[ i ] /= mMaxVal;
		}
	}
*/
	//mMaxVal *= 0.99;
}

float *FFT_FFTW::getInputBuffer( void )
{
	return( (float *)mInput );
}

float *FFT_FFTW::getOutputBuffer( void )
{
	return( (float *)mOutput );
}
