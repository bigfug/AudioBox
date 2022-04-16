/////////////////////////////////////////////////////////////////////////////
// Name:        AudioBoxVJJuniorWindow.cpp
// Purpose:     
// Author:      Alex May
// Modified by: 
// Created:     17/11/2008 14:24:52
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

#include "AudioBoxVJJuniorWindow.h"

////@begin XPM images
////@end XPM images


/*!
 * AudioBoxVJJuniorWindow type definition
 */

IMPLEMENT_DYNAMIC_CLASS( AudioBoxVJJuniorWindow, wxDialog )


/*!
 * AudioBoxVJJuniorWindow event table definition
 */

BEGIN_EVENT_TABLE( AudioBoxVJJuniorWindow, wxDialog )

////@begin AudioBoxVJJuniorWindow event table entries
////@end AudioBoxVJJuniorWindow event table entries

END_EVENT_TABLE()


/*!
 * AudioBoxVJJuniorWindow constructors
 */

AudioBoxVJJuniorWindow::AudioBoxVJJuniorWindow()
{
    Init();
}

AudioBoxVJJuniorWindow::AudioBoxVJJuniorWindow( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*!
 * AudioBoxVJJuniorWindow creator
 */

bool AudioBoxVJJuniorWindow::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin AudioBoxVJJuniorWindow creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end AudioBoxVJJuniorWindow creation
    return true;
}


/*!
 * AudioBoxVJJuniorWindow destructor
 */

AudioBoxVJJuniorWindow::~AudioBoxVJJuniorWindow()
{
////@begin AudioBoxVJJuniorWindow destruction
    GetAuiManager().UnInit();
////@end AudioBoxVJJuniorWindow destruction
}


/*!
 * Member initialisation
 */

void AudioBoxVJJuniorWindow::Init()
{
////@begin AudioBoxVJJuniorWindow member initialisation
////@end AudioBoxVJJuniorWindow member initialisation
}


/*!
 * Control creation for AudioBoxVJJuniorWindow
 */

void AudioBoxVJJuniorWindow::CreateControls()
{    
////@begin AudioBoxVJJuniorWindow content construction
    AudioBoxVJJuniorWindow* itemFrame1 = this;

    GetAuiManager().SetManagedWindow(this);

    wxMenuBar* menuBar = new wxMenuBar;
    wxMenu* itemMenu3 = new wxMenu;
    itemMenu3->Append(ID_MENU, _("E&xit"), _T(""), wxITEM_NORMAL);
    menuBar->Append(itemMenu3, _("&File"));
    itemFrame1->SetMenuBar(menuBar);

    wxToolBar* itemToolBar5 = new wxToolBar( itemFrame1, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL|wxTB_NODIVIDER|wxSIMPLE_BORDER );
    wxStaticText* itemStaticText6 = new wxStaticText( itemToolBar5, wxID_STATIC, _("Min BPM:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemToolBar5->AddControl(itemStaticText6);
    wxSpinCtrl* itemSpinCtrl7 = new wxSpinCtrl( itemToolBar5, ID_SPINCTRL8, _T("40"), wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 30, 180, 40 );
    itemToolBar5->AddControl(itemSpinCtrl7);
    wxStaticText* itemStaticText8 = new wxStaticText( itemToolBar5, wxID_STATIC, _("Max BPM:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemToolBar5->AddControl(itemStaticText8);
    wxSpinCtrl* itemSpinCtrl9 = new wxSpinCtrl( itemToolBar5, ID_SPINCTRL9, _T("40"), wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 40, 180, 40 );
    itemToolBar5->AddControl(itemSpinCtrl9);
    itemToolBar5->Realize();
    itemFrame1->GetAuiManager().AddPane(itemToolBar5, wxAuiPaneInfo()
        .ToolbarPane().Name(_T("Pane1")).Top().Layer(10).LeftDockable(false).RightDockable(false).BottomDockable(false).CaptionVisible(false).CloseButton(false).DestroyOnClose(false).Resizable(false).Floatable(false).Movable(false).PaneBorder(false));

    wxAuiNotebook* itemAuiNotebook10 = new wxAuiNotebook( itemFrame1, ID_AUINOTEBOOK, wxDefaultPosition, wxDefaultSize, 0 );

    wxPanel* itemPanel11 = new wxPanel( itemAuiNotebook10, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxFlexGridSizer* itemFlexGridSizer12 = new wxFlexGridSizer(2, 2, 0, 0);
    itemFlexGridSizer12->AddGrowableCol(1);
    itemPanel11->SetSizer(itemFlexGridSizer12);

    wxStaticText* itemStaticText13 = new wxStaticText( itemPanel11, wxID_STATIC, _("Input Device:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer12->Add(itemStaticText13, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString itemChoice14Strings;
    wxChoice* itemChoice14 = new wxChoice( itemPanel11, ID_CHOICE, wxDefaultPosition, wxDefaultSize, itemChoice14Strings, 0 );
    itemChoice14->Enable(false);
    itemFlexGridSizer12->Add(itemChoice14, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText15 = new wxStaticText( itemPanel11, wxID_STATIC, _("Sample Rate:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer12->Add(itemStaticText15, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString itemChoice16Strings;
    wxChoice* itemChoice16 = new wxChoice( itemPanel11, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, itemChoice16Strings, 0 );
    itemChoice16->Enable(false);
    itemFlexGridSizer12->Add(itemChoice16, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer12->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxToggleButton* itemToggleButton18 = new wxToggleButton( itemPanel11, ID_TOGGLEBUTTON, _("Toggle"), wxDefaultPosition, wxDefaultSize, 0 );
    itemToggleButton18->SetValue(false);
    itemFlexGridSizer12->Add(itemToggleButton18, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemAuiNotebook10->AddPage(itemPanel11, _("Audio"), false);

    wxPanel* itemPanel19 = new wxPanel( itemAuiNotebook10, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer20 = new wxBoxSizer(wxVERTICAL);
    itemPanel19->SetSizer(itemBoxSizer20);

    wxFlexGridSizer* itemFlexGridSizer21 = new wxFlexGridSizer(2, 2, 0, 0);
    itemFlexGridSizer21->AddGrowableCol(1);
    itemBoxSizer20->Add(itemFlexGridSizer21, 0, wxGROW|wxALL, 0);
    wxStaticText* itemStaticText22 = new wxStaticText( itemPanel19, wxID_STATIC, _("Output Device:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer21->Add(itemStaticText22, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString itemChoice23Strings;
    wxChoice* itemChoice23 = new wxChoice( itemPanel19, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, itemChoice23Strings, 0 );
    itemChoice23->Enable(false);
    itemFlexGridSizer21->Add(itemChoice23, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText24 = new wxStaticText( itemPanel19, wxID_STATIC, _("Channel:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer21->Add(itemStaticText24, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSpinCtrl* itemSpinCtrl25 = new wxSpinCtrl( itemPanel19, ID_SPINCTRL, _T("1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 16, 1 );
    itemSpinCtrl25->Enable(false);
    itemFlexGridSizer21->Add(itemSpinCtrl25, 0, wxALIGN_CENTER_HORIZONTAL|wxGROW|wxALL, 5);

    wxStaticLine* itemStaticLine26 = new wxStaticLine( itemPanel19, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer20->Add(itemStaticLine26, 0, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer27 = new wxFlexGridSizer(2, 5, 0, 0);
    itemFlexGridSizer27->AddGrowableCol(1);
    itemFlexGridSizer27->AddGrowableCol(2);
    itemBoxSizer20->Add(itemFlexGridSizer27, 0, wxGROW|wxALL, 0);
    wxStaticText* itemStaticText28 = new wxStaticText( itemPanel19, wxID_STATIC, _("Signal"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer27->Add(itemStaticText28, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText29 = new wxStaticText( itemPanel19, wxID_STATIC, _("Course CC"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer27->Add(itemStaticText29, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText30 = new wxStaticText( itemPanel19, wxID_STATIC, _("Fine CC"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer27->Add(itemStaticText30, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText31 = new wxStaticText( itemPanel19, wxID_STATIC, _("HiRes"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer27->Add(itemStaticText31, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText32 = new wxStaticText( itemPanel19, wxID_STATIC, _("Active"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer27->Add(itemStaticText32, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText33 = new wxStaticText( itemPanel19, wxID_STATIC, _("Saw Wave:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer27->Add(itemStaticText33, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSpinCtrl* itemSpinCtrl34 = new wxSpinCtrl( itemPanel19, ID_SPINCTRL1, _T("1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 128, 1 );
    itemFlexGridSizer27->Add(itemSpinCtrl34, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSpinCtrl* itemSpinCtrl35 = new wxSpinCtrl( itemPanel19, ID_SPINCTRL2, _T("1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 128, 1 );
    itemFlexGridSizer27->Add(itemSpinCtrl35, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCheckBox* itemCheckBox36 = new wxCheckBox( itemPanel19, ID_CHECKBOX, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox36->SetValue(false);
    itemFlexGridSizer27->Add(itemCheckBox36, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCheckBox* itemCheckBox37 = new wxCheckBox( itemPanel19, ID_CHECKBOX1, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox37->SetValue(false);
    itemFlexGridSizer27->Add(itemCheckBox37, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText38 = new wxStaticText( itemPanel19, wxID_STATIC, _("Saw Wave x2:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer27->Add(itemStaticText38, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSpinCtrl* itemSpinCtrl39 = new wxSpinCtrl( itemPanel19, ID_SPINCTRL4, _T("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0 );
    itemFlexGridSizer27->Add(itemSpinCtrl39, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSpinCtrl* itemSpinCtrl40 = new wxSpinCtrl( itemPanel19, ID_SPINCTRL5, _T("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0 );
    itemFlexGridSizer27->Add(itemSpinCtrl40, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCheckBox* itemCheckBox41 = new wxCheckBox( itemPanel19, ID_CHECKBOX4, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox41->SetValue(false);
    itemFlexGridSizer27->Add(itemCheckBox41, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCheckBox* itemCheckBox42 = new wxCheckBox( itemPanel19, ID_CHECKBOX5, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox42->SetValue(false);
    itemFlexGridSizer27->Add(itemCheckBox42, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText43 = new wxStaticText( itemPanel19, wxID_STATIC, _("Saw Wave /2:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer27->Add(itemStaticText43, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSpinCtrl* itemSpinCtrl44 = new wxSpinCtrl( itemPanel19, ID_SPINCTRL6, _T("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0 );
    itemFlexGridSizer27->Add(itemSpinCtrl44, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSpinCtrl* itemSpinCtrl45 = new wxSpinCtrl( itemPanel19, ID_SPINCTRL7, _T("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 0 );
    itemFlexGridSizer27->Add(itemSpinCtrl45, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCheckBox* itemCheckBox46 = new wxCheckBox( itemPanel19, ID_CHECKBOX6, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox46->SetValue(false);
    itemFlexGridSizer27->Add(itemCheckBox46, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCheckBox* itemCheckBox47 = new wxCheckBox( itemPanel19, ID_CHECKBOX7, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox47->SetValue(false);
    itemFlexGridSizer27->Add(itemCheckBox47, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine48 = new wxStaticLine( itemPanel19, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer20->Add(itemStaticLine48, 0, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer49 = new wxFlexGridSizer(2, 5, 0, 0);
    itemBoxSizer20->Add(itemFlexGridSizer49, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxStaticText* itemStaticText50 = new wxStaticText( itemPanel19, wxID_STATIC, _("Pulse"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer49->Add(itemStaticText50, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText51 = new wxStaticText( itemPanel19, wxID_STATIC, _("CC"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer49->Add(itemStaticText51, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText52 = new wxStaticText( itemPanel19, wxID_STATIC, _("Active"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer49->Add(itemStaticText52, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText53 = new wxStaticText( itemPanel19, wxID_STATIC, _("Note"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer49->Add(itemStaticText53, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText54 = new wxStaticText( itemPanel19, wxID_STATIC, _("Active"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer49->Add(itemStaticText54, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText55 = new wxStaticText( itemPanel19, wxID_STATIC, _("Beat:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer49->Add(itemStaticText55, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSpinCtrl* itemSpinCtrl56 = new wxSpinCtrl( itemPanel19, ID_SPINCTRL3, _T("1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 128, 1 );
    itemFlexGridSizer49->Add(itemSpinCtrl56, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCheckBox* itemCheckBox57 = new wxCheckBox( itemPanel19, ID_CHECKBOX2, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox57->SetValue(false);
    itemFlexGridSizer49->Add(itemCheckBox57, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString itemChoice58Strings;
    itemChoice58Strings.Add(_("C--1"));
    wxChoice* itemChoice58 = new wxChoice( itemPanel19, ID_CHOICE3, wxDefaultPosition, wxDefaultSize, itemChoice58Strings, 0 );
    itemChoice58->SetStringSelection(_("C--1"));
    itemFlexGridSizer49->Add(itemChoice58, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCheckBox* itemCheckBox59 = new wxCheckBox( itemPanel19, ID_CHECKBOX3, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox59->SetValue(false);
    itemFlexGridSizer49->Add(itemCheckBox59, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemAuiNotebook10->AddPage(itemPanel19, _("MIDI"), false);

    itemFrame1->GetAuiManager().AddPane(itemAuiNotebook10, wxAuiPaneInfo()
        .Name(_T("Pane2")).Centre().CaptionVisible(false).CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false));

    wxStatusBar* itemStatusBar60 = new wxStatusBar( itemFrame1, ID_STATUSBAR, wxST_SIZEGRIP|wxNO_BORDER );
    itemStatusBar60->SetFieldsCount(2);
    itemFrame1->SetStatusBar(itemStatusBar60);

    GetAuiManager().Update();

////@end AudioBoxVJJuniorWindow content construction
}


/*!
 * Should we show tooltips?
 */

bool AudioBoxVJJuniorWindow::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap AudioBoxVJJuniorWindow::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin AudioBoxVJJuniorWindow bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end AudioBoxVJJuniorWindow bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon AudioBoxVJJuniorWindow::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin AudioBoxVJJuniorWindow icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end AudioBoxVJJuniorWindow icon retrieval
}
