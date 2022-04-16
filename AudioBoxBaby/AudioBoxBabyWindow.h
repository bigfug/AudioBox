/////////////////////////////////////////////////////////////////////////////
// Name:        AudioBoxBabyWindow.h
// Purpose:     
// Author:      Alex May
// Modified by: 
// Created:     09/11/2008 22:07:49
// RCS-ID:      
// Copyright:   Copyright Quadratura Limited
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _AUDIOBOXBABYWINDOW_H_
#define _AUDIOBOXBABYWINDOW_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/frame.h"
#include "wx/tglbtn.h"
#include "wx/statusbr.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class wxToggleButton;
class wxStatusBar;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_AUDIOBOXBABYWINDOW 10000
#define ID_PANEL 10001
#define ID_AUDIO_DEVICE_CHOICE 10002
#define ID_AUDIO_SAMPLE_RATE_CHOICE 10003
#define ID_SAMPLE_BUTTON 10009
#define ID_LEFT_AMPL_GAUGE 10004
#define ID_RIGHT_AMPL_GAUGE 10005
#define ID_TEMPO_CERT_GAUGE 10006
#define ID_BEAT_PHASE_GAUGE 10010
#define wxID_BEAT_TEXT 10011
#define ID_BEAT_SUB_HALF 10012
#define ID_BEAT_SUB_QUARTER 10013
#define ID_BEAT_ADD_QUARTER 10014
#define ID_BEAT_ADD_HALF 10015
#define ID_BEAT_LOCK 10008
#define ID_BEAT_START_BUTTON 10016
#define ID_STATUSBAR 10007
#define SYMBOL_AUDIOBOXBABYWINDOW_STYLE wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_AUDIOBOXBABYWINDOW_TITLE _("AudioBox Baby")
#define SYMBOL_AUDIOBOXBABYWINDOW_IDNAME ID_AUDIOBOXBABYWINDOW
#define SYMBOL_AUDIOBOXBABYWINDOW_SIZE wxSize(400, 350)
#define SYMBOL_AUDIOBOXBABYWINDOW_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * AudioBoxBabyWindow class declaration
 */

class AudioBoxBabyWindow: public wxFrame
{    
    DECLARE_CLASS( AudioBoxBabyWindow )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    AudioBoxBabyWindow();
    AudioBoxBabyWindow( wxWindow* parent, wxWindowID id = SYMBOL_AUDIOBOXBABYWINDOW_IDNAME, const wxString& caption = SYMBOL_AUDIOBOXBABYWINDOW_TITLE, const wxPoint& pos = SYMBOL_AUDIOBOXBABYWINDOW_POSITION, const wxSize& size = SYMBOL_AUDIOBOXBABYWINDOW_SIZE, long style = SYMBOL_AUDIOBOXBABYWINDOW_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_AUDIOBOXBABYWINDOW_IDNAME, const wxString& caption = SYMBOL_AUDIOBOXBABYWINDOW_TITLE, const wxPoint& pos = SYMBOL_AUDIOBOXBABYWINDOW_POSITION, const wxSize& size = SYMBOL_AUDIOBOXBABYWINDOW_SIZE, long style = SYMBOL_AUDIOBOXBABYWINDOW_STYLE );

    /// Destructor
    ~AudioBoxBabyWindow();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin AudioBoxBabyWindow event handler declarations

    /// wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_AUDIO_DEVICE_CHOICE
    void OnAudioDeviceChoiceSelected( wxCommandEvent& event );

    /// wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_AUDIO_SAMPLE_RATE_CHOICE
    void OnAudioSampleRateChoiceSelected( wxCommandEvent& event );

    /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_SAMPLE_BUTTON
    void OnSampleButtonClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BEAT_SUB_HALF
    void OnBeatSubHalfClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BEAT_SUB_QUARTER
    void OnBeatSubQuarterClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BEAT_ADD_QUARTER
    void OnBeatAddQuarterClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BEAT_ADD_HALF
    void OnBeatAddHalfClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_BEAT_LOCK
    void OnBeatLockClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BEAT_START_BUTTON
    void OnBeatStartButtonClick( wxCommandEvent& event );

////@end AudioBoxBabyWindow event handler declarations

	void OnAudioReceived( AudioCaptureEvent &pEvent );
	void OnTimer( wxTimerEvent &pEvent );

////@begin AudioBoxBabyWindow member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end AudioBoxBabyWindow member function declarations

	void updateSampleRates( void );

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin AudioBoxBabyWindow member variables
    wxChoice* mAudioDeviceChoice;
    wxChoice* mAudioSampleRate;
    wxToggleButton* mAudioSampleButton;
    wxGauge* mLeftAmplGauge;
    wxGauge* mRightAmplGauge;
    wxGauge* mTempoCertGauge;
    wxGauge* mBeatPhaseGauge;
    wxStaticText* mBeatText;
    wxToggleButton* mBeatLock;
    wxButton* mBeatStart;
    wxStatusBar* mStatusBar;
////@end AudioBoxBabyWindow member variables

	AudioBoxLib			mAudioEngine;
	wxTimer				mTimer;
};

#endif
    // _AUDIOBOXBABYWINDOW_H_
