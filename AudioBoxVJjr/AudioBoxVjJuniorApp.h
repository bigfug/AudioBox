/////////////////////////////////////////////////////////////////////////////
// Name:        AudioBoxVjJuniorApp.h
// Purpose:     
// Author:      Alex May
// Modified by: 
// Created:     17/11/2008 14:18:03
// RCS-ID:      
// Copyright:   Copyright Quadratura Limited
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _AUDIOBOXVJJUNIORAPP_H_
#define _AUDIOBOXVJJUNIORAPP_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
#include "AudioBoxVJJuniorWindow.h"
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
 * AudioBoxVjJuniorApp class declaration
 */

class AudioBoxVjJuniorApp: public wxApp
{    
    DECLARE_CLASS( AudioBoxVjJuniorApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    AudioBoxVjJuniorApp();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin AudioBoxVjJuniorApp event handler declarations

////@end AudioBoxVjJuniorApp event handler declarations

////@begin AudioBoxVjJuniorApp member function declarations

////@end AudioBoxVjJuniorApp member function declarations

////@begin AudioBoxVjJuniorApp member variables
////@end AudioBoxVjJuniorApp member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(AudioBoxVjJuniorApp)
////@end declare app

#endif
    // _AUDIOBOXVJJUNIORAPP_H_
