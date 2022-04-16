/////////////////////////////////////////////////////////////////////////////
// Name:        gdfg.cpp
// Purpose:     
// Author:      Alex May
// Modified by: 
// Created:     17/11/2008 14:52:40
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

#include "gdfg.h"

////@begin XPM images

////@end XPM images


/*!
 * gdfg type definition
 */

IMPLEMENT_DYNAMIC_CLASS( gdfg, wxDialog )


/*!
 * gdfg event table definition
 */

BEGIN_EVENT_TABLE( gdfg, wxDialog )

////@begin gdfg event table entries
////@end gdfg event table entries

END_EVENT_TABLE()


/*!
 * gdfg constructors
 */

gdfg::gdfg()
{
    Init();
}

gdfg::gdfg( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * gdfg creator
 */

bool gdfg::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin gdfg creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end gdfg creation
    return true;
}


/*!
 * gdfg destructor
 */

gdfg::~gdfg()
{
////@begin gdfg destruction
////@end gdfg destruction
}


/*!
 * Member initialisation
 */

void gdfg::Init()
{
////@begin gdfg member initialisation
////@end gdfg member initialisation
}


/*!
 * Control creation for gdfg
 */

void gdfg::CreateControls()
{    
////@begin gdfg content construction
    gdfg* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

////@end gdfg content construction
}


/*!
 * Should we show tooltips?
 */

bool gdfg::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap gdfg::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin gdfg bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end gdfg bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon gdfg::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin gdfg icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end gdfg icon retrieval
}
