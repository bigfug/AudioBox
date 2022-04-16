/////////////////////////////////////////////////////////////////////////////
// Name:        AudioBoxBabyWindow.cpp
// Purpose:     
// Author:      Alex May
// Modified by: 
// Created:     09/11/2008 22:07:49
// RCS-ID:      
// Copyright:   Copyright Quadratura Limited
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "AudioBoxBabyApp.h"
#include "AudioBoxBabyWindow.h"

////@begin XPM images
////@end XPM images


/*!
 * AudioBoxBabyWindow type definition
 */

IMPLEMENT_CLASS( AudioBoxBabyWindow, wxFrame )


/*!
 * AudioBoxBabyWindow event table definition
 */

BEGIN_EVENT_TABLE( AudioBoxBabyWindow, wxFrame )

////@begin AudioBoxBabyWindow event table entries
    EVT_CHOICE( ID_AUDIO_DEVICE_CHOICE, AudioBoxBabyWindow::OnAudioDeviceChoiceSelected )

    EVT_CHOICE( ID_AUDIO_SAMPLE_RATE_CHOICE, AudioBoxBabyWindow::OnAudioSampleRateChoiceSelected )

    EVT_TOGGLEBUTTON( ID_SAMPLE_BUTTON, AudioBoxBabyWindow::OnSampleButtonClick )

    EVT_BUTTON( ID_BEAT_SUB_HALF, AudioBoxBabyWindow::OnBeatSubHalfClick )

    EVT_BUTTON( ID_BEAT_SUB_QUARTER, AudioBoxBabyWindow::OnBeatSubQuarterClick )

    EVT_BUTTON( ID_BEAT_ADD_QUARTER, AudioBoxBabyWindow::OnBeatAddQuarterClick )

    EVT_BUTTON( ID_BEAT_ADD_HALF, AudioBoxBabyWindow::OnBeatAddHalfClick )

    EVT_TOGGLEBUTTON( ID_BEAT_LOCK, AudioBoxBabyWindow::OnBeatLockClick )

    EVT_BUTTON( ID_BEAT_START_BUTTON, AudioBoxBabyWindow::OnBeatStartButtonClick )

////@end AudioBoxBabyWindow event table entries

	EVT_AUDIO_EVENT( wxID_ANY, AudioBoxBabyWindow::OnAudioReceived )

	EVT_TIMER( wxID_ANY, AudioBoxBabyWindow::OnTimer )
END_EVENT_TABLE()


/*!
 * AudioBoxBabyWindow constructors
 */

AudioBoxBabyWindow::AudioBoxBabyWindow()
{
    Init();
}

AudioBoxBabyWindow::AudioBoxBabyWindow( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}


/*!
 * AudioBoxBabyWindow creator
 */

bool AudioBoxBabyWindow::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin AudioBoxBabyWindow creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end AudioBoxBabyWindow creation
    return true;
}


/*!
 * AudioBoxBabyWindow destructor
 */

AudioBoxBabyWindow::~AudioBoxBabyWindow()
{
////@begin AudioBoxBabyWindow destruction
////@end AudioBoxBabyWindow destruction
}


/*!
 * Member initialisation
 */

void AudioBoxBabyWindow::Init()
{
////@begin AudioBoxBabyWindow member initialisation
    mAudioDeviceChoice = NULL;
    mAudioSampleRate = NULL;
    mAudioSampleButton = NULL;
    mLeftAmplGauge = NULL;
    mRightAmplGauge = NULL;
    mTempoCertGauge = NULL;
    mBeatPhaseGauge = NULL;
    mBeatText = NULL;
    mBeatLock = NULL;
    mBeatStart = NULL;
    mStatusBar = NULL;
////@end AudioBoxBabyWindow member initialisation
}


/*!
 * Control creation for AudioBoxBabyWindow
 */

void AudioBoxBabyWindow::CreateControls()
{    
////@begin AudioBoxBabyWindow content construction
    AudioBoxBabyWindow* itemFrame1 = this;

    wxPanel* itemPanel2 = new wxPanel( itemFrame1, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemPanel2->SetSizer(itemBoxSizer3);

    wxFlexGridSizer* itemFlexGridSizer4 = new wxFlexGridSizer(2, 2, 0, 0);
    itemFlexGridSizer4->AddGrowableCol(1);
    itemBoxSizer3->Add(itemFlexGridSizer4, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText5 = new wxStaticText( itemPanel2, wxID_STATIC, _("Audio Device:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText5, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString mAudioDeviceChoiceStrings;
    mAudioDeviceChoice = new wxChoice( itemPanel2, ID_AUDIO_DEVICE_CHOICE, wxDefaultPosition, wxDefaultSize, mAudioDeviceChoiceStrings, 0 );
    mAudioDeviceChoice->Enable(false);
    itemFlexGridSizer4->Add(mAudioDeviceChoice, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( itemPanel2, wxID_STATIC, _("Sample Rate:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText7, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString mAudioSampleRateStrings;
    mAudioSampleRate = new wxChoice( itemPanel2, ID_AUDIO_SAMPLE_RATE_CHOICE, wxDefaultPosition, wxDefaultSize, mAudioSampleRateStrings, 0 );
    mAudioSampleRate->Enable(false);
    itemFlexGridSizer4->Add(mAudioSampleRate, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText9 = new wxStaticText( itemPanel2, wxID_STATIC, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText9, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    mAudioSampleButton = new wxToggleButton( itemPanel2, ID_SAMPLE_BUTTON, _("Sample"), wxDefaultPosition, wxDefaultSize, 0 );
    mAudioSampleButton->SetValue(false);
    mAudioSampleButton->Enable(false);
    itemFlexGridSizer4->Add(mAudioSampleButton, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText11 = new wxStaticText( itemPanel2, wxID_STATIC, _("Left:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText11, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    mLeftAmplGauge = new wxGauge( itemPanel2, ID_LEFT_AMPL_GAUGE, 1000, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
    mLeftAmplGauge->SetValue(0);
    itemFlexGridSizer4->Add(mLeftAmplGauge, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText13 = new wxStaticText( itemPanel2, wxID_STATIC, _("Right:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText13, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    mRightAmplGauge = new wxGauge( itemPanel2, ID_RIGHT_AMPL_GAUGE, 1000, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
    mRightAmplGauge->SetValue(0);
    itemFlexGridSizer4->Add(mRightAmplGauge, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText15 = new wxStaticText( itemPanel2, wxID_STATIC, _("Tempo Certainty:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText15, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    mTempoCertGauge = new wxGauge( itemPanel2, ID_TEMPO_CERT_GAUGE, 1000, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
    mTempoCertGauge->SetValue(0);
    itemFlexGridSizer4->Add(mTempoCertGauge, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText17 = new wxStaticText( itemPanel2, wxID_STATIC, _("Beat Phase:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText17, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    mBeatPhaseGauge = new wxGauge( itemPanel2, ID_BEAT_PHASE_GAUGE, 1000, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
    mBeatPhaseGauge->SetValue(0);
    itemFlexGridSizer4->Add(mBeatPhaseGauge, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer19 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer19, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    mBeatText = new wxStaticText( itemPanel2, wxID_BEAT_TEXT, _("BEAT 1"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxST_NO_AUTORESIZE );
    itemBoxSizer19->Add(mBeatText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton21 = new wxButton( itemPanel2, ID_BEAT_SUB_HALF, _("-1/2"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer19->Add(itemButton21, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton22 = new wxButton( itemPanel2, ID_BEAT_SUB_QUARTER, _("-1/4"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer19->Add(itemButton22, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton23 = new wxButton( itemPanel2, ID_BEAT_ADD_QUARTER, _("+1/4"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer19->Add(itemButton23, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton24 = new wxButton( itemPanel2, ID_BEAT_ADD_HALF, _("+1/2"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer19->Add(itemButton24, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    mBeatLock = new wxToggleButton( itemPanel2, ID_BEAT_LOCK, _("Lock"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    mBeatLock->SetValue(false);
    itemBoxSizer19->Add(mBeatLock, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    mBeatStart = new wxButton( itemPanel2, ID_BEAT_START_BUTTON, _("Beat 1"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
    itemBoxSizer19->Add(mBeatStart, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    mStatusBar = new wxStatusBar( itemFrame1, ID_STATUSBAR, wxNO_BORDER );
    mStatusBar->SetFieldsCount(2);
    mStatusBar->SetStatusText(_("Status: Stopped"), 0);
    mStatusBar->SetStatusText(_("Tempo:"), 1);
    itemFrame1->SetStatusBar(mStatusBar);

////@end AudioBoxBabyWindow content construction

	const DeviceNameHash	&AudioNames = wxGetApp().getAudioCapture().getInputDeviceNames();
	const long				 DeviceId   = wxGetApp().getConfig().Read( _T( "AudioDeviceId" ), wxGetApp().getAudioCapture().getDefaultInputDeviceId() );

	for( DeviceNameHash::const_iterator it = AudioNames.begin() ; it != AudioNames.end() ; it++ )
	{
		bool		Inserted = false;

		for( int i = 0 ; !Inserted && i < mAudioDeviceChoice->GetCount() ; i++ )
		{
			if( it->first < mAudioDeviceChoice->GetString( i ) )
			{
				mAudioDeviceChoice->Insert( it->first, i );

				if( DeviceId == it->second )
				{
					mAudioDeviceChoice->SetSelection( i );
				}

				Inserted = true;
			}
		}

		if( !Inserted )
		{
			mAudioDeviceChoice->Append( it->first );

			if( DeviceId == it->second )
			{
				mAudioDeviceChoice->SetSelection( mAudioDeviceChoice->GetCount() - 1 );
			}
		}
	}

	if( mAudioDeviceChoice->GetCount() > 0 )
	{
		mAudioDeviceChoice->Enable();

		updateSampleRates();
	}
}

void AudioBoxBabyWindow::updateSampleRates( void )
{
	const double		*SampleRates;
	int					 SampleSelect = 0;
	long				 SampleRate = wxGetApp().getConfig().Read( _T( "AudioSampleRate" ), 11025 );

	if( ( SampleRates = wxGetApp().getAudioCapture().getSampleRates() ) != 0 )
	{
		for( int i = 0 ; SampleRates[ i ] != 0.0 ; i++ )
		{
			wxString		SampleRateString;

			SampleRateString.sprintf( _T( "%d" ), (int)SampleRates[ i ] );

			if( (int)SampleRates[ i ] == SampleRate )
			{
				SampleSelect = i;
			}

			mAudioSampleRate->Append( SampleRateString, (void *)&SampleRates[ i ] );
		}

		wxGetApp().getConfig().Write( _T( "AudioSampleRate" ), (long)SampleRates[ SampleSelect ] );

		mAudioSampleRate->SetSelection( SampleSelect );
		mAudioSampleRate->Enable();
		mAudioSampleButton->Enable();
	}
}

/*!
 * Should we show tooltips?
 */

bool AudioBoxBabyWindow::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap AudioBoxBabyWindow::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin AudioBoxBabyWindow bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end AudioBoxBabyWindow bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon AudioBoxBabyWindow::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin AudioBoxBabyWindow icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end AudioBoxBabyWindow icon retrieval
}


/*!
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_AUDIO_DEVICE_CHOICE
 */

void AudioBoxBabyWindow::OnAudioDeviceChoiceSelected( wxCommandEvent& event )
{
	DeviceNameHash				 DeviceNames    = wxGetApp().getAudioCapture().getInputDeviceNames();
	DeviceNameHash::iterator	 DeviceIterator = DeviceNames.find( mAudioDeviceChoice->GetStringSelection() );

	mAudioSampleRate->Clear();
	mAudioSampleRate->Disable();
	mAudioSampleButton->Disable();

	if( DeviceIterator != DeviceNames.end() )
	{
		wxGetApp().mAudioCapture.setInputDeviceId( DeviceIterator->second );

		wxGetApp().getConfig().Write( _T( "AudioDeviceId" ), DeviceIterator->second );

		updateSampleRates();
	}
}


/*!
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_AUDIO_SAMPLE_RATE_CHOICE
 */

void AudioBoxBabyWindow::OnAudioSampleRateChoiceSelected( wxCommandEvent &pEvent )
{
	const double *SampleRate = (const double *)pEvent.GetClientData();

	wxGetApp().getConfig().Write( _T( "AudioSampleRate" ), (long)*SampleRate );
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_SAMPLE_BUTTON
 */

void AudioBoxBabyWindow::OnSampleButtonClick( wxCommandEvent& event )
{
	if( mAudioSampleButton->GetValue() )
	{
		const unsigned int		SampleRate      = wxGetApp().getConfig().Read( _T( "AudioSampleRate" ), 11025 );
		const unsigned int		SamplesPerFrame = 256;

		mAudioDeviceChoice->Disable();
		mAudioSampleRate->Disable();

		mStatusBar->SetStatusText( _( "Status: Initialising" ) );

		mAudioEngine.start( SampleRate, SamplesPerFrame );

		mTimer.SetOwner( this, wxID_ANY );
		mTimer.Start( 40 );

		wxGetApp().getAudioCapture().captureStart( this, SampleRate, SamplesPerFrame );

		mStatusBar->SetStatusText( _( "Status: Sampling" ) );
	}
	else
	{
		mStatusBar->SetStatusText( _( "Status: Cleaning up" ) );

		mTimer.Stop();

		wxGetApp().getAudioCapture().captureStop();

		mAudioEngine.stop();

		mStatusBar->SetStatusText( _( "Status: Stopped" ) );

		mAudioDeviceChoice->Enable();
		mAudioSampleRate->Enable();
	}
}

void AudioBoxBabyWindow::OnAudioReceived( AudioCaptureEvent &pEvent )
{
	if( !mAudioSampleButton->GetValue() )
	{
		return;
	}

	mAudioEngine.onAudio( pEvent );
}

void AudioBoxBabyWindow::OnTimer( wxTimerEvent &pEvent )
{
	if( !mAudioSampleButton->GetValue() )
	{
		return;
	}
	
	mAudioEngine.onTimer( pEvent );

	mLeftAmplGauge->SetValue( (int)( mAudioEngine.getAnalysisWave().getAmplitudeLeft() * 1000.0 ) );
	mRightAmplGauge->SetValue( (int)( mAudioEngine.getAnalysisWave().getAmplitudeRight() * 1000.0 ) );
	mTempoCertGauge->SetValue( (int)( mAudioEngine.getAnalysisBeat().getTempoConfidence() * 10 ) );
	mBeatPhaseGauge->SetValue( (int)( ( 1.0 - mAudioEngine.getAnalysisBeat().getBeatPhase() ) * 1000.0 ) );

	SetStatusText( wxString::Format( _( "Tempo: %d" ), (int)mAudioEngine.getAnalysisBeat().getBeatsPerMinute() ), 1 );

	mBeatText->SetLabel( wxString::Format( _( "BEAT %d" ), mAudioEngine.getAnalysisBeat().getBeat() + 1 ) );
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BEAT_SUB_HALF
 */

void AudioBoxBabyWindow::OnBeatSubHalfClick( wxCommandEvent& event )
{
	mAudioEngine.getAnalysisBeat().addBeatOffset( -0.5 );
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BEAT_SUB_QUARTER
 */

void AudioBoxBabyWindow::OnBeatSubQuarterClick( wxCommandEvent& event )
{
	mAudioEngine.getAnalysisBeat().addBeatOffset( -0.25 );
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BEAT_ADD_QUARTER
 */

void AudioBoxBabyWindow::OnBeatAddQuarterClick( wxCommandEvent& event )
{
	mAudioEngine.getAnalysisBeat().addBeatOffset( 0.25 );
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BEAT_ADD_HALF
 */

void AudioBoxBabyWindow::OnBeatAddHalfClick( wxCommandEvent& event )
{
	mAudioEngine.getAnalysisBeat().addBeatOffset( 0.5 );
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_BEAT_LOCK
 */

void AudioBoxBabyWindow::OnBeatLockClick( wxCommandEvent& event )
{
	mAudioEngine.getAnalysisBeat().setBeatLocked( mBeatLock->GetValue() );
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BEAT_START_BUTTON
 */

void AudioBoxBabyWindow::OnBeatStartButtonClick( wxCommandEvent& event )
{
	mAudioEngine.getAnalysisBeat().setBeat();
}

