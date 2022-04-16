#pragma once

#include "stdafx.h"
#include "AudioCaptureEvent.h"

enum
{
    ID_BLAH = 26
};

WX_DECLARE_STRING_HASH_MAP( int, DeviceNameHash );

class AudioCapture
{
private:
	int					 mInputDevice;
	PaStream			*mStream;
	wxEvtHandler		*mHandler;
	int					 mSamplesPerFrame;
	int					 mSampleRate;
	PaDeviceIndex		 mDeviceId;
	bool				 mDeviceOpen;
	float				*mAudioFrameLeft;
	float				*mAudioFrameRight;
	float				*mAudioFrameMono;
	DeviceNameHash		 mInputDeviceNames;
	long				 mLatency;
	int					 mNumInputs;
	int					 mSampleRateCount;
public:
	AudioCapture( void );
	~AudioCapture(void);

	int initialise(void);
	int shutdown(void);
	static int __cdecl callbackStub( const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData );
	int callback( const float *inputBuffer, float *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags );

	int captureStart( wxEvtHandler *pHandler, int pSampleRate, int pSamplesPerFrame );
	int captureStop( void );

	const DeviceNameHash &getInputDeviceNames( void );
	int getDefaultInputDeviceId( void );

	void setInputDeviceId( int pDeviceId );
	int getSampleRatesCount( void );
	const double *getSampleRates( void );

	int getNumberOfBuffers( void );
	long getInputLatency( void );

	const int getDeviceId( void );

	bool hasAudioConfig( void ) const;
	void showAudioConfig( void );
};
