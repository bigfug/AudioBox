#include "StdAfx.h"
#include "AudioCaptureEvent.h"

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

DEFINE_EVENT_TYPE( wxEVT_AUDIO_EVENT )

AudioCaptureEvent::AudioCaptureEvent( unsigned long pSamples, const unsigned int pChannels, wxEventType commandType, int id )
: mSamples( pSamples ), mChannels( pChannels ), wxCommandEvent( commandType, id )
{
	wxASSERT( mSamples > 0 && mSamples < 2048 );

	if( mChannels > 1 )
	{
		mDataLeft  = new float[ pSamples ];
		mDataRight = new float[ pSamples ];
		mDataMono  = 0;
	}
	else
	{
		mDataLeft  = 0;
		mDataRight = 0;
		mDataMono  = new float[ pSamples ];
	}
}

AudioCaptureEvent::~AudioCaptureEvent( void )
{
	SAFE_DELETE_ARRAY( mDataLeft );
	SAFE_DELETE_ARRAY( mDataRight );
	SAFE_DELETE_ARRAY( mDataMono );
}

wxEvent* AudioCaptureEvent::Clone() const
{
	AudioCaptureEvent		*Clone = new AudioCaptureEvent( mSamples, mChannels, GetEventType(), GetId() );

	if( Clone != 0 )
	{
		if( mChannels > 1 )
		{
			memcpy( Clone->mDataLeft,  mDataLeft,  sizeof( float ) * mSamples );
			memcpy( Clone->mDataRight, mDataRight, sizeof( float ) * mSamples );
		}
		else
		{
			memcpy( Clone->mDataMono,  mDataMono,  sizeof( float ) * mSamples );
		}

		Clone->mFlags      = mFlags;
		Clone->mTimeInfo   = mTimeInfo;
		Clone->mStreamTime = mStreamTime;
	}

	return( Clone );
}
