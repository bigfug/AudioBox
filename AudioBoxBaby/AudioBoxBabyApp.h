/////////////////////////////////////////////////////////////////////////////
// Name:        AudioBoxBabyApp.h
// Purpose:     
// Author:      Alex May
// Modified by: 
// Created:     09/11/2008 22:00:36
// RCS-ID:      
// Copyright:   Copyright Quadratura Limited
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _AUDIOBOXBABYAPP_H_
#define _AUDIOBOXBABYAPP_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
#include "AudioBoxBabyWindow.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
////@end control identifiers

/*!
 * AudioBoxBabyApp class declaration
 */

class AudioBoxBabyApp: public wxApp
{    
    DECLARE_CLASS( AudioBoxBabyApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    AudioBoxBabyApp();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin AudioBoxBabyApp event handler declarations

////@end AudioBoxBabyApp event handler declarations

////@begin AudioBoxBabyApp member function declarations

////@end AudioBoxBabyApp member function declarations

	inline AudioCapture &getAudioCapture( void )
	{
		return( mAudioCapture );
	}

	inline wxConfig &getConfig( void )
	{
		return( *mConfig );
	}

////@begin AudioBoxBabyApp member variables
////@end AudioBoxBabyApp member variables

	AudioCapture		 mAudioCapture;
	wxConfig			*mConfig;
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(AudioBoxBabyApp)
////@end declare app

#endif
    // _AUDIOBOXBABYAPP_H_
