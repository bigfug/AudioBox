#pragma once

class AudioCaptureEvent : public wxCommandEvent
{
protected:
	PaStreamCallbackTimeInfo	 mTimeInfo;
	PaStreamCallbackFlags		 mFlags;
	float						*mDataLeft;
	float						*mDataRight;
	float						*mDataMono;
	const unsigned long			 mSamples;
	const unsigned int			 mChannels;
	PaTime						 mStreamTime;
public:
	AudioCaptureEvent( unsigned long pSamples, const unsigned int pChannels, wxEventType commandType = wxEVT_NULL, int id = 0 );

	virtual ~AudioCaptureEvent( void );

	const PaTime getStreamTime( void ) const
	{
		return( mStreamTime );
	}

	void setStreamTime( const PaTime pStreamTime )
	{
		mStreamTime = pStreamTime;
	}

	const PaStreamCallbackTimeInfo &getTimeInfo( void ) const
	{
		return( mTimeInfo );
	}

	void setTimeInfo( const PaStreamCallbackTimeInfo &pTimeInfo )
	{
		mTimeInfo = pTimeInfo;
	}

	PaStreamCallbackFlags getFlags( void ) const
	{
		return( mFlags );
	}

	void setFlags( const PaStreamCallbackFlags pFlags )
	{
		mFlags = pFlags;
	}

	float *getAudioDataLeft( void ) const
	{
		return( mDataLeft );
	}

	float *getAudioDataRight( void ) const
	{
		return( mDataRight );
	}

	float *getAudioDataMono( void ) const
	{
		return( mDataMono );
	}

	unsigned long getAudioSampleCount( void ) const
	{
		return( mSamples );
	}

	// required for sending with wxPostEvent()

    wxEvent* Clone() const;
};

DECLARE_EVENT_TYPE( wxEVT_AUDIO_EVENT, -1 )

typedef void (wxEvtHandler::*AudioCaptureEventFunction)(AudioCaptureEvent&);

#define EVT_AUDIO_EVENT(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_AUDIO_EVENT, id, -1, \
    (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) \
    wxStaticCastEvent( AudioCaptureEventFunction, & fn ), (wxObject *) NULL ),
