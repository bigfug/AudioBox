#pragma once

class FFT
{
public:
	FFT( const int pNumSamples ) {}

	virtual void PowerSpectrum( void ) = 0;

	virtual float *getInputBuffer( void ) = 0;
	virtual float *getOutputBuffer( void ) = 0;
};

class FFT_FFT : virtual public FFT
{
private:
	int				**mFFTBitTable;
	int				  mNumSamples;
	float			 *tmpReal;
	float			 *tmpImag;
	float			 *RealOut;
	float			 *ImagOut;
	float			 *mInputBuffer;
	float			 *mOutputBuffer;

public:
	FFT_FFT( const int pNumSamples );
	~FFT_FFT( void );

	int FastReverseBits( int i, int NumBits );
	int NumberOfBitsNeeded(int PowerOfTwo);
	int ReverseBits(int index, int NumBits);
	void DoFFT(int NumSamples,
         bool InverseTransform,
         float *RealIn, float *ImagIn, float *RealOut, float *ImagOut);
	void RealFFT(float *RealIn, float *RealOut, float *ImagOut);

	void PowerSpectrum( void );

	float *getInputBuffer( void );
	float *getOutputBuffer( void );
};

#include "fftw3.h"

class FFT_FFTW : public FFT
{
private:
	float				*mInput;
	float				*mOutput;
	float				*mScale;
	fftwf_plan			 mPlan;
	const int			 mNumSamples;
	float				 mMaxVal;
public:
	FFT_FFTW( const int pNumSamples );
	~FFT_FFTW( void );

	void PowerSpectrum( void );

	float *getInputBuffer( void );
	float *getOutputBuffer( void );
};

