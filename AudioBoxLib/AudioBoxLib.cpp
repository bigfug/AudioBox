#include "StdAfx.h"
#include "AudioBoxLib.h"
#include "AudioCaptureEvent.h"

static const int SLIDING_WINDOW_SIZE = 4096;
static const int SLIDING_WINDOW_COUNT = 8;

AudioBoxLib::AudioBoxLib( void )
: mSlidingWindow( 0 ), mTimerId( 0 )
{
}

AudioBoxLib::~AudioBoxLib( void )
{
	stop();
}

void AudioBoxLib::start( const UINT pSampleRate, const UINT pSamplesPerFrame )
{
	mSampleRate      = pSampleRate;
	mSamplesPerFrame = pSamplesPerFrame;
	mAudioTime       = 0;
	mAudioSamplesReceived = 0;

	mSlidingWindow = new SlidingWindowFloat( mSamplesPerFrame, SLIDING_WINDOW_SIZE, SLIDING_WINDOW_COUNT );

	TIMECAPS		TimerCaps;
	MMRESULT		Result;

	if( ( Result = timeGetDevCaps( &TimerCaps, sizeof( TimerCaps ) ) ) != TIMERR_NOERROR )
	{
		wxLogFatalError( _( "Can't get the timer capabilities" ) );
	}

	mTimePeriod = max( TimerCaps.wPeriodMin, 10 );

	if( ( mTimeBeginResult = timeBeginPeriod( mTimePeriod ) ) != TIMERR_NOERROR )
	{
		wxLogFatalError( _( "Can't get set the timer to a resolution of %u" ), mTimePeriod );
	}

	if( ( mTimerId = timeSetEvent( mTimePeriod, 0, AudioBoxLib::timeProc, reinterpret_cast<DWORD_PTR>( this ), TIME_PERIODIC | TIME_KILL_SYNCHRONOUS ) ) == 0 )
	{
		wxLogFatalError( _( "Can't start the multimedia timer with a resolution of %u" ), mTimePeriod );
	}

	for( int i = 0 ; i < 16 ; i++ )
	{
		mEq[ i ] = 1.0;
	}

	mAnalysisWave.initialise( mSampleRate, pSamplesPerFrame );
	mAnalysisFFT.initialise( mSampleRate, pSamplesPerFrame );
	mAnalysisBeat.initialise( mSampleRate, pSamplesPerFrame );
	mAnalysisFreqBins.initialise( mSampleRate, pSamplesPerFrame );
}

void AudioBoxLib::stop( void )
{
	MMRESULT		Result;

	if( mTimerId != 0 )
	{
		if( ( Result = timeKillEvent( mTimerId ) ) != TIMERR_NOERROR )
		{
			wxLogError( _( "Can't stop the multimedia timer" ) );
		}

		mTimerId = 0;
	}

	if( mTimeBeginResult != TIMERR_NOERROR )
	{
		timeEndPeriod( mTimePeriod );
	}

	mAnalysisBeat.deinitialise();
	mAnalysisFFT.deinitialise();
	mAnalysisWave.deinitialise();
	mAnalysisFreqBins.deinitialise();

	SAFE_DELETE( mSlidingWindow );
}

void AudioBoxLib::onAudio( AudioCaptureEvent &pEvent )
{
	if( mAudioTime == 0 )
	{
		mAudioStart = timeGetTime();
	}

	mAnalysisWave.processData( pEvent.getAudioDataLeft(), pEvent.getAudioDataRight(), pEvent.getAudioDataMono() );

	//---------------------------------------------------------------------
	// Add the data to the sliding window

	mSlidingWindow->addData( mAnalysisWave.getAmplifiedInput(), mAudioStart + mAudioTime );

	const int WindowCount = mSlidingWindow->getAvailableWindows();

	//---------------------------------------------------------------------
	// Process the available windows

	for( int WindowIndex = 0 ; WindowIndex < WindowCount ; WindowIndex++ )
	{
		const float			*Window           = mSlidingWindow->getWindow( WindowIndex );
		const PtTimestamp	 WindowTime       = mSlidingWindow->getWindowTime( WindowIndex );
		const long			 WindowLength     = mSlidingWindow->getWindowLength();

		mAnalysisFFT.processData( 0, 0, Window );

		mAnalysisFreqBins.processData( mAnalysisFFT.getFFT(), mEq );

		mAnalysisBeat.processData( mAnalysisFFT.getHFC(), mAnalysisFFT.getHFCAverage().getAverage(), WindowTime, WindowLength );

//		mAnalysisBeat.processData( mAnalysisFreqBins.getBeatAvg(), mAnalysisFreqBins.getBeatAvgTotal(), WindowTime, WindowLength );
	}

	//---------------------------------------------------------------------
	// Update the audio timer

	mAudioSamplesReceived++;

	mAudioTime = (long)( 1000.0 * ( (double)( mSamplesPerFrame * mAudioSamplesReceived ) / (double)mSampleRate ) );
}

void AudioBoxLib::onTimer( wxTimerEvent &pEvent )
{
	mAnalysisBeat.processBeats();

	//mAnalysisBeat.processTime( timeGetTime() );
}

void CALLBACK AudioBoxLib::timeProc( UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2 )
{
	AudioBoxLib		*AudioEngine = reinterpret_cast<AudioBoxLib *>( dwUser );

	AudioEngine->mAnalysisBeat.processTime( timeGetTime() );

	if( AudioEngine->mAnalysisBeat.isBeat() )
	{
	}
}
