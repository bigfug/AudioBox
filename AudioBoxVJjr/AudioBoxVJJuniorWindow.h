/////////////////////////////////////////////////////////////////////////////
// Name:        AudioBoxVJJuniorWindow.h
// Purpose:     
// Author:      Alex May
// Modified by: 
// Created:     17/11/2008 14:24:52
// RCS-ID:      
// Copyright:   Copyright Quadratura Limited
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _AUDIOBOXVJJUNIORWINDOW_H_
#define _AUDIOBOXVJJUNIORWINDOW_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/aui/framemanager.h"
#include "wx/frame.h"
#include "wx/toolbar.h"
#include "wx/spinctrl.h"
#include "wx/aui/auibook.h"
#include "wx/tglbtn.h"
#include "wx/statline.h"
#include "wx/statusbr.h"
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
#define ID_AUDIOBOXVJJUNIORWINDOW 10000
#define ID_MENU 10012
#define ID_TOOLBAR 10002
#define ID_SPINCTRL8 10029
#define ID_SPINCTRL9 10030
#define ID_AUINOTEBOOK 10003
#define ID_PANEL 10005
#define ID_CHOICE 10007
#define ID_CHOICE1 10008
#define ID_TOGGLEBUTTON 10009
#define ID_PANEL1 10006
#define ID_CHOICE2 10010
#define ID_SPINCTRL 10011
#define ID_SPINCTRL1 10013
#define ID_SPINCTRL2 10015
#define ID_CHECKBOX 10014
#define ID_CHECKBOX1 10016
#define ID_SPINCTRL4 10021
#define ID_SPINCTRL5 10022
#define ID_CHECKBOX4 10023
#define ID_CHECKBOX5 10024
#define ID_SPINCTRL6 10025
#define ID_SPINCTRL7 10026
#define ID_CHECKBOX6 10027
#define ID_CHECKBOX7 10028
#define ID_SPINCTRL3 10017
#define ID_CHECKBOX2 10018
#define ID_CHOICE3 10019
#define ID_CHECKBOX3 10020
#define ID_STATUSBAR 10004
#define SYMBOL_AUDIOBOXVJJUNIORWINDOW_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_AUDIOBOXVJJUNIORWINDOW_TITLE _("AudioBox VJ Junior")
#define SYMBOL_AUDIOBOXVJJUNIORWINDOW_IDNAME ID_AUDIOBOXVJJUNIORWINDOW
#define SYMBOL_AUDIOBOXVJJUNIORWINDOW_SIZE wxSize(435, 450)
#define SYMBOL_AUDIOBOXVJJUNIORWINDOW_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * AudioBoxVJJuniorWindow class declaration
 */

class AudioBoxVJJuniorWindow: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( AudioBoxVJJuniorWindow )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    AudioBoxVJJuniorWindow();
    AudioBoxVJJuniorWindow( wxWindow* parent, wxWindowID id = SYMBOL_AUDIOBOXVJJUNIORWINDOW_IDNAME, const wxString& caption = SYMBOL_AUDIOBOXVJJUNIORWINDOW_TITLE, const wxPoint& pos = SYMBOL_AUDIOBOXVJJUNIORWINDOW_POSITION, const wxSize& size = SYMBOL_AUDIOBOXVJJUNIORWINDOW_SIZE, long style = SYMBOL_AUDIOBOXVJJUNIORWINDOW_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_AUDIOBOXVJJUNIORWINDOW_IDNAME, const wxString& caption = SYMBOL_AUDIOBOXVJJUNIORWINDOW_TITLE, const wxPoint& pos = SYMBOL_AUDIOBOXVJJUNIORWINDOW_POSITION, const wxSize& size = SYMBOL_AUDIOBOXVJJUNIORWINDOW_SIZE, long style = SYMBOL_AUDIOBOXVJJUNIORWINDOW_STYLE );

    /// Destructor
    ~AudioBoxVJJuniorWindow();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin AudioBoxVJJuniorWindow event handler declarations

////@end AudioBoxVJJuniorWindow event handler declarations

////@begin AudioBoxVJJuniorWindow member function declarations

    /// Returns the AUI manager object
    wxAuiManager& GetAuiManager() { return m_auiManager; }

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end AudioBoxVJJuniorWindow member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin AudioBoxVJJuniorWindow member variables
    wxAuiManager m_auiManager;
////@end AudioBoxVJJuniorWindow member variables
};

/*!
 * AudioBoxVJJuniorWindow class declaration
 */

class AudioBoxVJJuniorWindow: public wxFrame
{    
    DECLARE_CLASS( AudioBoxVJJuniorWindow )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    AudioBoxVJJuniorWindow();
    AudioBoxVJJuniorWindow( wxWindow* parent, wxWindowID id = SYMBOL_AUDIOBOXVJJUNIORWINDOW_IDNAME, const wxString& caption = SYMBOL_AUDIOBOXVJJUNIORWINDOW_TITLE, const wxPoint& pos = SYMBOL_AUDIOBOXVJJUNIORWINDOW_POSITION, const wxSize& size = SYMBOL_AUDIOBOXVJJUNIORWINDOW_SIZE, long style = SYMBOL_AUDIOBOXVJJUNIORWINDOW_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_AUDIOBOXVJJUNIORWINDOW_IDNAME, const wxString& caption = SYMBOL_AUDIOBOXVJJUNIORWINDOW_TITLE, const wxPoint& pos = SYMBOL_AUDIOBOXVJJUNIORWINDOW_POSITION, const wxSize& size = SYMBOL_AUDIOBOXVJJUNIORWINDOW_SIZE, long style = SYMBOL_AUDIOBOXVJJUNIORWINDOW_STYLE );

    /// Destructor
    ~AudioBoxVJJuniorWindow();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin AudioBoxVJJuniorWindow event handler declarations
////@end AudioBoxVJJuniorWindow event handler declarations

////@begin AudioBoxVJJuniorWindow member function declarations
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end AudioBoxVJJuniorWindow member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin AudioBoxVJJuniorWindow member variables
////@end AudioBoxVJJuniorWindow member variables
};

#endif
    // _AUDIOBOXVJJUNIORWINDOW_H_
