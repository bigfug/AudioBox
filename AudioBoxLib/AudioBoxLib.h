#pragma once

#include "AnalysisWave.h"
#include "SlidingWindow.h"
#include "AnalysisFFT.h"
#include "AnalysisBeat.h"
#include "AnalysisFreqBins.h"
#include <mmsystem.h>

typedef unsigned int		UINT;

class AudioCaptureEvent;

class AudioBoxLib
{
protected:
	UINT				 mSampleRate;
	UINT				 mSamplesPerFrame;
	AnalysisWave		 mAnalysisWave;
	AnalysisFFT			 mAnalysisFFT;
	AnalysisBeat		 mAnalysisBeat;
	AnalysisFreqBins	 mAnalysisFreqBins;
	PtTimestamp			 mAudioStart;
	long				 mAudioTime;
	long				 mAudioSamplesReceived;
	SlidingWindowFloat	*mSlidingWindow;
	UINT				 mTimePeriod;
	MMRESULT			 mTimeBeginResult;
	UINT				 mTimerId;
	float				 mEq[ 16 ];

	static void CALLBACK timeProc( UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2 );
public:
	AudioBoxLib( void );
	~AudioBoxLib( void );

	void start( const UINT pSampleRate, const UINT pSamplesPerFrame );
	void stop( void );

	void onAudio( AudioCaptureEvent &pEvent );
	void onTimer( wxTimerEvent &pEvent );

	inline AnalysisWave &getAnalysisWave( void )
	{
		return( mAnalysisWave );
	}

	inline AnalysisBeat &getAnalysisBeat( void )
	{
		return( mAnalysisBeat );
	}
};
