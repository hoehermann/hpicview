/***************************************************************
 * Name:      hpicviewMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Hermann Höhne (hermann@hehoe.de)
 * Created:   2018-03-31
 * Copyright: Hermann Höhne (www.hehoe.de)
 * License:   GNU GPLv3
 **************************************************************/

#include <wx/filedlg.h> // for wxFileDialog in OnOpen
#include "hpicviewMain.hpp"
#include "droptarget.hpp"
#include "extensions.hpp"
#include "../resources/icon.svg.xpm"

hpicviewFrame::hpicviewFrame(wxFrame *frame)
    : GUIFrame(frame), m_dirty(false), m_image_extensions(GetImageExts())
{
    this->SetIcon(wxIcon(icon_svg_xpm));
    const int status_widths[] = {-70,-20,-10};
    this->SetStatusWidths(3, status_widths);
    this->SetStatusText(_("No image."), STATUSBAR_COLUMN_MAIN);
    //this->SetStatusText(wxbuildinfo(short_f), STATUSBAR_COLUMN_INDEX);
    this->SetDropTarget(
        new FileDropTarget<hpicviewFrame>(&hpicviewFrame::OnDropFile, this)
    );
}

hpicviewFrame::~hpicviewFrame()
{
}

void hpicviewFrame::OnClose(wxCloseEvent&)
{
    Destroy();
}

void hpicviewFrame::OnQuit(wxCommandEvent&)
{
    Destroy();
}

void hpicviewFrame::OnOpen(wxCommandEvent&) {
    wxString exts("All built-in image files|");
    exts << GetImageExtWildcard(m_image_extensions);
    exts << "|";

    wxFileDialog openFileDialog(
        this, _("Open file"), "", "",
        exts + // "All built-in image files "+wxImage::GetImageExtWildcard()+"|"
        "JPEG files|*.jpg;*.jpeg;*.JPG|" +
        "All files|*.*",
        wxFD_OPEN, wxDefaultPosition
    );

    if (openFileDialog.ShowModal() == wxID_OK) {
		OpenFile(openFileDialog.GetPath());
    }
}

void hpicviewFrame::SetConfiguration() {
    // TODO: read/write configuration from/to file
    // this->menuViewZoomFitAuto->Checked(true);
}

void hpicviewFrame::OnToggleFullScreen(wxCommandEvent&) {
    this->ShowFullScreen(!this->IsFullScreen());
}

void hpicviewFrame::OnSize(wxSizeEvent& se) {
    this->FitAndDisplay();
    se.Skip();
}

void hpicviewFrame::OnEscape(wxCommandEvent& ce) {
    if (this->IsFullScreen()) {
        this->OnToggleFullScreen(ce);
    } else {
        this->OnQuit(ce);
    }
}

bool hpicviewFrame::OnDropFile(wxCoord, wxCoord, const wxArrayString& paths) {
    if (paths.size() > 0) {
        this->OpenFile(paths[0]);
        return true;
    }
    return false;
}
