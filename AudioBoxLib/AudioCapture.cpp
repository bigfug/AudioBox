#include "StdAfx.h"
#include "AudioCapture.h"

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

AudioCapture::AudioCapture( void )
{
	this->mDeviceId   = paNoDevice;
	this->mDeviceOpen = false;
	this->mHandler    = 0;

	mSampleRateCount = 0;
}

AudioCapture::~AudioCapture( void )
{
}

int AudioCapture::initialise( void )
{
	PaHostApiIndex			 ApiCount;
	const	PaHostApiInfo	*ApiInfo;
	PaDeviceIndex			 DeviceIndex;
	const	PaDeviceInfo	*DeviceInfo;
	PaError					 Error;
	wxString				 Name;

    if( ( Error = Pa_Initialize() ) != paNoError )
	{
		wxMessageDialog( 0, wxString( Pa_GetErrorText( Error ), wxConvUTF8 ), _T( "Audio Device Error" ), wxOK );

		return( Error );
	}

	ApiCount = Pa_GetHostApiCount();

	for( PaHostApiIndex i = 0 ; i < ApiCount ; i++ )
	{
		if( ( ApiInfo = Pa_GetHostApiInfo( i ) ) == NULL )
		{
			continue;
		}

		for( int j = 0 ; j < ApiInfo->deviceCount ; j++ )
		{
			DeviceIndex = Pa_HostApiDeviceIndexToDeviceIndex( i, j );

			if( DeviceIndex == paInvalidHostApi )
			{
				break;
			}

			if( DeviceIndex == paInvalidDevice )
			{
				continue;
			}

			if( ( DeviceInfo = Pa_GetDeviceInfo( DeviceIndex ) ) == NULL )
			{
				continue;
			}

			if( DeviceInfo->maxInputChannels > 0 )
			{
				Name = wxString( ApiInfo->name, wxConvUTF8 );
				Name += _T( ": " );
				Name += wxString( DeviceInfo->name, wxConvUTF8 );

				this->mInputDeviceNames[ Name ] = DeviceIndex;
			}
		}
	}

	return( paNoError );
}

int AudioCapture::captureStart( wxEvtHandler *pHandler, int pSampleRate, int pSamplesPerFrame )
{
	const PaDeviceInfo		*DeviceInfo;
	const PaStreamInfo		*StreamInfo;
	PaStreamParameters		 InputParams;
	PaError					 Error;
	double					 Latency;

	this->mSampleRate      = pSampleRate;
	this->mSamplesPerFrame = pSamplesPerFrame;

	DeviceInfo = Pa_GetDeviceInfo( this->mDeviceId );

	this->mAudioFrameLeft  = new float[ pSamplesPerFrame ];
	this->mAudioFrameRight = new float[ pSamplesPerFrame ];
	this->mAudioFrameMono  = new float[ pSamplesPerFrame ];

//	this->mNumBuffers = 0;

	//this->mNumInputs = min( DeviceInfo->maxInputChannels, 2 );
	this->mNumInputs = DeviceInfo->maxInputChannels;

	memset( &InputParams, 0, sizeof( InputParams ) );

	InputParams.device           = mDeviceId;
	InputParams.channelCount     = mNumInputs;
	InputParams.sampleFormat     = paFloat32;
	InputParams.suggestedLatency = DeviceInfo->defaultLowInputLatency;

	if( ( Error = Pa_OpenStream( &this->mStream, &InputParams, NULL, this->mSampleRate, this->mSamplesPerFrame, paNoFlag, AudioCapture::callbackStub, this ) ) != paNoError )
	{
		wxMessageDialog	Dialog( 0, wxString( Pa_GetErrorText( Error ), wxConvUTF8 ), _T( "Audio Device Error" ), wxOK );

		Dialog.ShowModal();

		return( Error );
	}

	StreamInfo = Pa_GetStreamInfo( mStream );

	Latency = (double)this->mSampleRate / (double)this->mSamplesPerFrame;
	Latency = 1000.0 / Latency;

	this->mLatency = (long)( Latency + StreamInfo->inputLatency );

	this->mHandler = pHandler;

	if( ( Error = Pa_StartStream( this->mStream ) ) != paNoError )
	{
		wxMessageDialog	Dialog( 0, wxString( Pa_GetErrorText( Error ), wxConvUTF8 ), _T( "Audio Device Error" ), wxOK );

		Dialog.ShowModal();

		return( Error );
	}

	return( paNoError );
}

int AudioCapture::captureStop( void )
{
	PaError		Error;

	if( this->mHandler == 0 )
	{
		return( -1 );
	}

	if( ( Error = Pa_AbortStream( this->mStream ) ) != paNoError )
	{
		wxMessageDialog	Dialog( 0, wxString( Pa_GetErrorText( Error ), wxConvUTF8 ), _T( "Audio Device Error" ), wxOK );

		Dialog.ShowModal();

		return( Error );
	}

	if( ( Error = Pa_CloseStream( this->mStream ) ) != paNoError )
	{
		wxMessageDialog	Dialog( 0, wxString( Pa_GetErrorText( Error ), wxConvUTF8 ), _T( "Audio Device Error" ), wxOK );

		Dialog.ShowModal();

		return( Error );
	}

	this->mHandler = 0;

	this->mStream = 0;

	SAFE_DELETE_ARRAY( mAudioFrameLeft );
	SAFE_DELETE_ARRAY( mAudioFrameRight );
	SAFE_DELETE_ARRAY( mAudioFrameMono );

	return( paNoError );
}

int AudioCapture::shutdown(void)
{
	PaError		Error;

	this->captureStop();

	if( ( Error = Pa_Terminate() ) != paNoError )
	{
		wxMessageDialog	Dialog( 0, wxString( Pa_GetErrorText( Error ), wxConvUTF8 ), _T( "Audio Device Error" ), wxOK );

		Dialog.ShowModal();

		return( Error );
	}

	this->mInputDeviceNames.clear();

	return( paNoError );
}

int __cdecl AudioCapture::callbackStub( const void *inputBuffer, void *outputBuffer, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData )
{
	return( reinterpret_cast<AudioCapture *>( userData )->callback( (float *)inputBuffer, (float *)outputBuffer, frameCount, timeInfo, statusFlags ) );
}

int AudioCapture::callback( const float *inputBuffer, float *outputBuffer, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags )
{
	if( this->mHandler != 0 )
	{
		AudioCaptureEvent		AudioEvent( frameCount, mNumInputs, wxEVT_AUDIO_EVENT, 0 );

/*
		For deinterlaced (which doesn't work!)

		if( mNumInputs >= 2 )
		{
			memcpy( mAudioFrameLeft,   inputBuffer, frameCount * sizeof( float ) );
			memcpy( mAudioFrameRight,  &inputBuffer[ frameCount ], frameCount * sizeof( float ) );

			for( int i = 0 ; i < frameCount ; i++ )
			{
				mAudioFrameMono[ i ] = mAudioFrameLeft[ i ] + mAudioFrameRight[ i ] / 2.0f;
			}

			AudioEvent.setAudioDataLeft( mAudioFrameLeft );
			AudioEvent.setAudioDataRight( mAudioFrameRight );
		}
		else
		{
			memcpy( mAudioFrameMono, inputBuffer, frameCount * sizeof( float ) );
		}
*/

		if( mNumInputs >= 2 )
		{
			float		*LeftPtr  = AudioEvent.getAudioDataLeft();
			float		*RightPtr = AudioEvent.getAudioDataRight();

			for( int i = 0 ; i < frameCount ; i++ )
			{
				const int Offset = i * mNumInputs;

				LeftPtr[ i ]  = inputBuffer[ Offset + 0 ];
				RightPtr[ i ] = inputBuffer[ Offset + 1 ];
			}
		}
		else
		{
			memcpy( AudioEvent.getAudioDataMono(), inputBuffer, frameCount * sizeof( float ) );
		}

		AudioEvent.setFlags( statusFlags );
		AudioEvent.setTimeInfo( *timeInfo );
		AudioEvent.setStreamTime( Pa_GetStreamTime( mStream ) );

		this->mHandler->AddPendingEvent( AudioEvent );
	}

	return( paNoError );
}

int AudioCapture::getDefaultInputDeviceId( void )
{
	return( Pa_GetDefaultInputDevice() );
}

const DeviceNameHash &AudioCapture::getInputDeviceNames( void )
{
	return( this->mInputDeviceNames );
}

void AudioCapture::setInputDeviceId( int pDeviceId )
{
	if( !this->mDeviceOpen )
	{
		this->mDeviceId  = pDeviceId;

		mSampleRateCount = 0;
	}
}

const double *AudioCapture::getSampleRates( void )
{
	if( mDeviceId == paNoDevice && ( mDeviceId = getDefaultInputDeviceId() ) == paNoDevice )
	{
		return( 0 );
	}

	const PaDeviceInfo		*DeviceInfo = Pa_GetDeviceInfo( this->mDeviceId );
	PaStreamParameters		 InputParams;
	static double			 SampleRates[ 10 ];
	double					*SampleRatePtr = SampleRates;

	memset( &InputParams, 0, sizeof( InputParams ) );

	InputParams.device           = this->mDeviceId;
	InputParams.channelCount     = DeviceInfo->maxInputChannels;
	InputParams.sampleFormat     = paFloat32;
	InputParams.suggestedLatency = DeviceInfo->defaultLowInputLatency;

	if( Pa_IsFormatSupported( &InputParams, 0, 11025.0 ) == paFormatIsSupported )
	{
		*SampleRatePtr++ = 11025.0;

		mSampleRateCount++;
	}

	if( Pa_IsFormatSupported( &InputParams, 0, 22050.0 ) == paFormatIsSupported )
	{
		*SampleRatePtr++ = 22050.0;

		mSampleRateCount++;
	}

	if( Pa_IsFormatSupported( &InputParams, 0, 32000.0 ) == paFormatIsSupported )
	{
		*SampleRatePtr++ = 32000.0;

		mSampleRateCount++;
	}

	if( Pa_IsFormatSupported( &InputParams, 0, 44100.0 ) == paFormatIsSupported )
	{
		*SampleRatePtr++ = 44100.0;

		mSampleRateCount++;
	}

	if( Pa_IsFormatSupported( &InputParams, 0, 48000.0 ) == paFormatIsSupported )
	{
		*SampleRatePtr++ = 48000.0;

		mSampleRateCount++;
	}

	if( Pa_IsFormatSupported( &InputParams, 0, 96000.0 ) == paFormatIsSupported )
	{
		*SampleRatePtr++ = 96000.0;

		mSampleRateCount++;
	}

	*SampleRatePtr = 0.0;

	return( SampleRates );
}

int AudioCapture::getSampleRatesCount( void )
{
	if( mSampleRateCount == 0 )
	{
		getSampleRates();
	}

	return( mSampleRateCount );
}

int AudioCapture::getNumberOfBuffers( void )
{
	return( 1 );
}

long AudioCapture::getInputLatency( void )
{
	return( this->mLatency );
}

const int AudioCapture::getDeviceId( void )
{
	return( this->mDeviceId );
}

bool AudioCapture::hasAudioConfig( void ) const
{
	const PaDeviceInfo		*DeviceInfo = Pa_GetDeviceInfo( mDeviceId );
	const PaHostApiInfo		*HostApiInfo = Pa_GetHostApiInfo( DeviceInfo->hostApi );

	switch( HostApiInfo->type )
	{
		case paASIO:
			return( true );
	}

	return( false );
}

PaError PaAsio_ShowControlPanel( PaDeviceIndex device, void* systemSpecific );

void AudioCapture::showAudioConfig( void )
{
	const PaDeviceInfo		*DeviceInfo = Pa_GetDeviceInfo( mDeviceId );
	const PaHostApiInfo		*HostApiInfo = Pa_GetHostApiInfo( DeviceInfo->hostApi );

	switch( HostApiInfo->type )
	{
		case paASIO:
			//PaAsio_ShowControlPanel( mDeviceId, 0 );
			break;
	}
}

