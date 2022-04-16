#include "StdAfx.h"
#include "Analysis.h"

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

Analysis::Analysis( void )
: mSampleRate( 0 ), mSamplesPerFrame( 0 )
{
}

Analysis::~Analysis( void )
{
}

bool Analysis::initialise( const int pSampleRate, const int pSamplesPerFrame )
{
	mSampleRate      = pSampleRate;
	mSamplesPerFrame = pSamplesPerFrame;

	return( true );
}

void Analysis::deinitialise( void )
{
}
