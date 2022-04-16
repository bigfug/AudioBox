/////////////////////////////////////////////////////////////////////////////
// Name:        gdfg.h
// Purpose:     
// Author:      Alex May
// Modified by: 
// Created:     17/11/2008 14:52:40
// RCS-ID:      
// Copyright:   Copyright Quadratura Limited
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _GDFG_H_
#define _GDFG_H_


/*!
 * Includes
 */

////@begin includes
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
#define ID_GDFG 10011
#define SYMBOL_GDFG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_GDFG_TITLE _("gdfg")
#define SYMBOL_GDFG_IDNAME ID_GDFG
#define SYMBOL_GDFG_SIZE wxSize(400, 300)
#define SYMBOL_GDFG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * gdfg class declaration
 */

class gdfg: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( gdfg )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    gdfg();
    gdfg( wxWindow* parent, wxWindowID id = SYMBOL_GDFG_IDNAME, const wxString& caption = SYMBOL_GDFG_TITLE, const wxPoint& pos = SYMBOL_GDFG_POSITION, const wxSize& size = SYMBOL_GDFG_SIZE, long style = SYMBOL_GDFG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_GDFG_IDNAME, const wxString& caption = SYMBOL_GDFG_TITLE, const wxPoint& pos = SYMBOL_GDFG_POSITION, const wxSize& size = SYMBOL_GDFG_SIZE, long style = SYMBOL_GDFG_STYLE );

    /// Destructor
    ~gdfg();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin gdfg event handler declarations
////@end gdfg event handler declarations

////@begin gdfg member function declarations
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end gdfg member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin gdfg member variables
////@end gdfg member variables
};

#endif
    // _GDFG_H_
