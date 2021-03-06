///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Jan  6 2021)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include "sstatbmp.h"
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/toolbar.h>
#include <wx/statbmp.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define idMenuQuit 1000
#define idMenuAbout 1001

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame
{
	private:

	protected:
		wxMenuBar* menubar;
		wxMenu* menuFile;
		wxMenu* m_menuImage;
		wxMenu* menuView;
		wxMenuItem* menuViewZoomFitAuto;
		wxMenuItem* menuViewUpscaleSmall;
		wxMenu* menuHelp;
		wxToolBar* toolBar;
		wxToolBarToolBase* toolOpen;
		wxToolBarToolBase* toolRotateLeft;
		wxToolBarToolBase* toolRotateRight;
		wxToolBarToolBase* toolZoomFit;
		wxToolBarToolBase* toolZoomIn;
		wxToolBarToolBase* toolZoomOut;
		wxToolBarToolBase* toolPrevious;
		wxToolBarToolBase* toolNext;
		wxToolBarToolBase* toolAbout;
		wxScrolledWindow* mainScrolledWindow;
		wxSelectableStaticBitmap* bitmap;
		wxStatusBar* statusBar;

		// Virtual event handlers, overide them in your derived class
		virtual void OnActivateApp( wxActivateEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRotateLeft( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRotateRight( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZoomFit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZoomIn( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnZoomOut( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPrevious( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNext( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnMotion( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnRightUp( wxMouseEvent& event ) { event.Skip(); }


	public:

		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("hpicview"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 670,560 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~GUIFrame();

};

