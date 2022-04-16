/////////////////////////////////////////////////////////////////////////////
// Name:        AudioBoxBabyApp.cpp
// Purpose:     
// Author:      Alex May
// Modified by: 
// Created:     09/11/2008 22:00:36
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

////@begin XPM images
////@end XPM images


/*!
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( AudioBoxBabyApp )
////@end implement app


/*!
 * AudioBoxBabyApp type definition
 */

IMPLEMENT_CLASS( AudioBoxBabyApp, wxApp )


/*!
 * AudioBoxBabyApp event table definition
 */

BEGIN_EVENT_TABLE( AudioBoxBabyApp, wxApp )

////@begin AudioBoxBabyApp event table entries
////@end AudioBoxBabyApp event table entries

END_EVENT_TABLE()


/*!
 * Constructor for AudioBoxBabyApp
 */

AudioBoxBabyApp::AudioBoxBabyApp()
{
    Init();
}


/*!
 * Member initialisation
 */

void AudioBoxBabyApp::Init()
{
////@begin AudioBoxBabyApp member initialisation
////@end AudioBoxBabyApp member initialisation
}

/*!
 * Initialisation for AudioBoxBabyApp
 */

bool AudioBoxBabyApp::OnInit()
{
	if( ( mConfig = new wxConfig( _T( "AudioBoxBaby" ) ) ) == 0 )
	{
		wxLogFatalError( _T( "Out of memory" ) );
	}

	if( mAudioCapture.initialise() != paNoError )
	{
		wxLogFatalError( _T( "Can't initialise audio system" ) );
	}

////@begin AudioBoxBabyApp initialisation
	// Remove the comment markers above and below this block
	// to make permanent changes to the code.

#if wxUSE_XPM
	wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif
	AudioBoxBabyWindow* mainWindow = new AudioBoxBabyWindow( NULL );
	mainWindow->Show(true);
////@end AudioBoxBabyApp initialisation

    return true;
}


/*!
 * Cleanup for AudioBoxBabyApp
 */

int AudioBoxBabyApp::OnExit()
{
	mAudioCapture.shutdown();

	SAFE_DELETE( mConfig );

////@begin AudioBoxBabyApp cleanup
	return wxApp::OnExit();
////@end AudioBoxBabyApp cleanup
}

