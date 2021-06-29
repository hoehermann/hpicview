///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Jan  6 2021)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUIFrame.h"

#include "../resources/arrow_left.svg.png.h"
#include "../resources/arrow_right.svg.png.h"
#include "../resources/fit.svg.png.h"
#include "../resources/folder_open.svg.png.h"
#include "../resources/icon.svg.png.h"
#include "../resources/question.svg.png.h"
#include "../resources/redo.svg.png.h"
#include "../resources/search_minus.svg.png.h"
#include "../resources/search_plus.svg.png.h"
#include "../resources/undo.svg.png.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	menubar = new wxMenuBar( 0 );
	menuFile = new wxMenu();
	wxMenuItem* menuFileOpen;
	menuFileOpen = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("&Open") ) + wxT('\t') + wxT("CTRL+O"), wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( menuFileOpen );

	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( menuFile, idMenuQuit, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
	menuFile->Append( menuFileQuit );

	menubar->Append( menuFile, wxT("&File") );

	m_menuImage = new wxMenu();
	wxMenuItem* menuImageRotateLeft;
	menuImageRotateLeft = new wxMenuItem( m_menuImage, wxID_ANY, wxString( wxT("Rotate &Left") ) + wxT('\t') + wxT("L"), wxEmptyString, wxITEM_NORMAL );
	m_menuImage->Append( menuImageRotateLeft );

	wxMenuItem* menuImageRotateRight;
	menuImageRotateRight = new wxMenuItem( m_menuImage, wxID_ANY, wxString( wxT("Rotate &Right") ) + wxT('\t') + wxT("R"), wxEmptyString, wxITEM_NORMAL );
	m_menuImage->Append( menuImageRotateRight );

	menubar->Append( m_menuImage, wxT("&Image") );

	menuView = new wxMenu();
	menuViewZoomFitAuto = new wxMenuItem( menuView, wxID_ANY, wxString( wxT("Zoom to Fit Automatically") ) , wxEmptyString, wxITEM_CHECK );
	menuView->Append( menuViewZoomFitAuto );
	menuViewZoomFitAuto->Check( true );

	menuViewUpscaleSmall = new wxMenuItem( menuView, wxID_ANY, wxString( wxT("Enlarge small images") ) , wxT("Small images are not displayed larger than they are."), wxITEM_CHECK );
	menuView->Append( menuViewUpscaleSmall );

	menubar->Append( menuView, wxT("View") );

	menuHelp = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( menuHelp, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	menuHelp->Append( menuHelpAbout );

	menubar->Append( menuHelp, wxT("&Help") );

	this->SetMenuBar( menubar );

	toolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	toolOpen = toolBar->AddTool( wxID_ANY, wxT("&Open"), folder_open_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Open image file…"), wxT("Open image file…"), NULL );

	toolBar->AddSeparator();

	toolRotateLeft = toolBar->AddTool( wxID_ANY, wxT("Rotate &Left"), undo_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Rotate Left"), wxT("Rotate JPEG Left"), NULL );

	toolRotateRight = toolBar->AddTool( wxID_ANY, wxT("Rotate &Right"), redo_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Rotate Right"), wxT("Rotate JPEG Right"), NULL );

	toolBar->AddSeparator();

	toolZoomFit = toolBar->AddTool( wxID_ANY, wxT("Zoom &to Fit"), fit_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Zoom to Fit"), wxT("Zoom to Fit"), NULL );

	toolZoomIn = toolBar->AddTool( wxID_ANY, wxT("Zoom &In"), search_plus_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Zoom In"), wxT("Zoom In"), NULL );

	toolZoomOut = toolBar->AddTool( wxID_ANY, wxT("Zoom O&ut"), search_minus_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Zoom Out"), wxT("Zoom Out"), NULL );

	toolBar->AddSeparator();

	toolPrevious = toolBar->AddTool( wxID_ANY, wxT("Previous"), arrow_left_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Previous"), wxT("Load previous file in directory"), NULL );

	toolNext = toolBar->AddTool( wxID_ANY, wxT("Next"), arrow_right_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("Next"), wxT("Load next file in directory"), NULL );

	toolBar->AddSeparator();

	toolAbout = toolBar->AddTool( wxID_ANY, wxT("tool"), question_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxT("About"), wxT("Show information about this application"), NULL );

	toolBar->Realize();

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );

	mainScrolledWindow = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	mainScrolledWindow->SetScrollRate( 5, 5 );
	wxBoxSizer* mainScrolledWindowSizer;
	mainScrolledWindowSizer = new wxBoxSizer( wxVERTICAL );

	bitmap = new wxSelectableStaticBitmap( mainScrolledWindow, wxID_ANY, icon_svg_png_to_wx_bitmap(), wxDefaultPosition, wxDefaultSize, 0 );
	mainScrolledWindowSizer->Add( bitmap, 1, wxEXPAND, 5 );


	mainScrolledWindow->SetSizer( mainScrolledWindowSizer );
	mainScrolledWindow->Layout();
	mainScrolledWindowSizer->Fit( mainScrolledWindow );
	mainSizer->Add( mainScrolledWindow, 1, wxEXPAND, 5 );


	this->SetSizer( mainSizer );
	this->Layout();
	statusBar = this->CreateStatusBar( 3, wxSTB_SIZEGRIP, wxID_ANY );

	// Connect Events
	this->Connect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( GUIFrame::OnActivateApp ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( GUIFrame::OnSize ) );
	menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnOpen ), this, menuFileOpen->GetId());
	menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ), this, menuFileQuit->GetId());
	m_menuImage->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnRotateLeft ), this, menuImageRotateLeft->GetId());
	m_menuImage->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnRotateRight ), this, menuImageRotateRight->GetId());
	menuHelp->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ), this, menuHelpAbout->GetId());
	this->Connect( toolOpen->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnOpen ) );
	this->Connect( toolRotateLeft->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnRotateLeft ) );
	this->Connect( toolRotateRight->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnRotateRight ) );
	this->Connect( toolZoomFit->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnZoomFit ) );
	this->Connect( toolZoomIn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnZoomIn ) );
	this->Connect( toolZoomOut->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnZoomOut ) );
	this->Connect( toolPrevious->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnPrevious ) );
	this->Connect( toolNext->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnNext ) );
	this->Connect( toolAbout->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	bitmap->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GUIFrame::OnLeftDown ), NULL, this );
	bitmap->Connect( wxEVT_MOTION, wxMouseEventHandler( GUIFrame::OnMotion ), NULL, this );
	bitmap->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( GUIFrame::OnRightUp ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( GUIFrame::OnActivateApp ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( GUIFrame::OnSize ) );
	this->Disconnect( toolOpen->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnOpen ) );
	this->Disconnect( toolRotateLeft->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnRotateLeft ) );
	this->Disconnect( toolRotateRight->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnRotateRight ) );
	this->Disconnect( toolZoomFit->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnZoomFit ) );
	this->Disconnect( toolZoomIn->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnZoomIn ) );
	this->Disconnect( toolZoomOut->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnZoomOut ) );
	this->Disconnect( toolPrevious->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnPrevious ) );
	this->Disconnect( toolNext->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnNext ) );
	this->Disconnect( toolAbout->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	bitmap->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GUIFrame::OnLeftDown ), NULL, this );
	bitmap->Disconnect( wxEVT_MOTION, wxMouseEventHandler( GUIFrame::OnMotion ), NULL, this );
	bitmap->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( GUIFrame::OnRightUp ), NULL, this );

}
