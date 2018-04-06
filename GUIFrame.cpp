///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 16 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUIFrame.h"

#include "resources/arrow_left.svg.png.h"
#include "resources/arrow_right.svg.png.h"
#include "resources/folder_open.svg.png.h"
#include "resources/question.svg.png.h"
#include "resources/redo.svg.png.h"
#include "resources/undo.svg.png.h"

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
	
	menuHelp = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( menuHelp, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	menuHelp->Append( menuHelpAbout );
	
	menubar->Append( menuHelp, wxT("&Help") ); 
	
	this->SetMenuBar( menubar );
	
	toolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	toolOpen = toolBar->AddTool( wxID_ANY, wxT("&Open"), folder_open_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	toolBar->AddSeparator(); 
	
	toolRotateLeft = toolBar->AddTool( wxID_ANY, wxT("Rotate &Left"), undo_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	toolRotateRight = toolBar->AddTool( wxID_ANY, wxT("Rotate &Right"), redo_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	toolBar->AddSeparator(); 
	
	toolPrevious = toolBar->AddTool( wxID_ANY, wxT("Previous"), arrow_left_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	toolNext = toolBar->AddTool( wxID_ANY, wxT("Next"), arrow_right_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	toolBar->AddSeparator(); 
	
	toolAbout = toolBar->AddTool( wxID_ANY, wxT("tool"), question_svg_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	toolBar->Realize(); 
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	mainScrolledWindow = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	mainScrolledWindow->SetScrollRate( 5, 5 );
	wxBoxSizer* mainScrolledWindowSizer;
	mainScrolledWindowSizer = new wxBoxSizer( wxVERTICAL );
	
	m_bitmap = new wxStaticBitmap( mainScrolledWindow, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	mainScrolledWindowSizer->Add( m_bitmap, 1, wxALL, 5 );
	
	
	mainScrolledWindow->SetSizer( mainScrolledWindowSizer );
	mainScrolledWindow->Layout();
	mainScrolledWindowSizer->Fit( mainScrolledWindow );
	mainSizer->Add( mainScrolledWindow, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	
	// Connect Events
	this->Connect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( GUIFrame::OnActivateApp ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( menuFileOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnOpen ) );
	this->Connect( menuFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Connect( menuImageRotateLeft->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnRotateLeft ) );
	this->Connect( menuImageRotateRight->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnRotateRight ) );
	this->Connect( menuHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	this->Connect( toolOpen->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnOpen ) );
	this->Connect( toolRotateLeft->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnRotateLeft ) );
	this->Connect( toolRotateRight->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnRotateRight ) );
	this->Connect( toolPrevious->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnPrevious ) );
	this->Connect( toolNext->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnNext ) );
	this->Connect( toolAbout->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnAbout ) );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( GUIFrame::OnActivateApp ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnOpen ) );
	this->Disconnect( idMenuQuit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnRotateLeft ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnRotateRight ) );
	this->Disconnect( idMenuAbout, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	this->Disconnect( toolOpen->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnOpen ) );
	this->Disconnect( toolRotateLeft->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnRotateLeft ) );
	this->Disconnect( toolRotateRight->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnRotateRight ) );
	this->Disconnect( toolPrevious->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnPrevious ) );
	this->Disconnect( toolNext->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnNext ) );
	this->Disconnect( toolAbout->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( GUIFrame::OnAbout ) );
	
}
