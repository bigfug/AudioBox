#pragma once

#define		WINDOW_RECTANGLE		(0)
#define		WINDOW_BARTLETT			(1)
#define		WINDOW_HAMMING			(2)
#define		WINDOW_HANNING			(3)

class AudioWindow
{
private:
	const	unsigned	int		 mNumSamples;
	const	unsigned	int		 mFunction;
	float			*mBufferLeft;
	float			*mBufferRight;
public:
	AudioWindow( const unsigned int pFunction, const unsigned int pNumSamples );
	~AudioWindow(void);
	static const unsigned int NumWindowFuncs();
	static char *WindowFuncName( const unsigned int whichFunction );

	void ProcessWindow( const float *pInput, float *pOutput );
	void WindowFunc( float *in );
};
