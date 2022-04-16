#pragma once

class Analysis
{
protected:
	int					 mSampleRate;
	int					 mSamplesPerFrame;
public:
	Analysis( void );

	virtual ~Analysis( void );

	bool initialise( const int pSampleRate, const int pSamplesPerFrame );

	void deinitialise( void );
};
