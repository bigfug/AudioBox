/////////////////////////////////////////////////////////////////////////////
// Name:        AudioBoxVjJuniorApp.cpp
// Purpose:     
// Author:      Alex May
// Modified by: 
// Created:     17/11/2008 14:18:03
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

#include "AudioBoxVjJuniorApp.h"

////@begin XPM images
////@end XPM images


/*!
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( AudioBoxVjJuniorApp )
////@end implement app


/*!
 * AudioBoxVjJuniorApp type definition
 */

IMPLEMENT_CLASS( AudioBoxVjJuniorApp, wxApp )


/*!
 * AudioBoxVjJuniorApp event table definition
 */

BEGIN_EVENT_TABLE( AudioBoxVjJuniorApp, wxApp )

////@begin AudioBoxVjJuniorApp event table entries
////@end AudioBoxVjJuniorApp event table entries

END_EVENT_TABLE()


/*!
 * Constructor for AudioBoxVjJuniorApp
 */

AudioBoxVjJuniorApp::AudioBoxVjJuniorApp()
{
    Init();
}


/*!
 * Member initialisation
 */

void AudioBoxVjJuniorApp::Init()
{
////@begin AudioBoxVjJuniorApp member initialisation
////@end AudioBoxVjJuniorApp member initialisation
}

/*!
 * Initialisation for AudioBoxVjJuniorApp
 */

bool AudioBoxVjJuniorApp::OnInit()
{    
////@begin AudioBoxVjJuniorApp initialisation
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
	AudioBoxVJJuniorWindow* mainWindow = new AudioBoxVJJuniorWindow(NULL);
	/* int returnValue = */ mainWindow->ShowModal();

	mainWindow->Destroy();
	// A modal dialog application should return false to terminate the app.
	return false;
////@end AudioBoxVjJuniorApp initialisation

    return true;
}


/*!
 * Cleanup for AudioBoxVjJuniorApp
 */

int AudioBoxVjJuniorApp::OnExit()
{    
////@begin AudioBoxVjJuniorApp cleanup
	return wxApp::OnExit();
////@end AudioBoxVjJuniorApp cleanup
}

