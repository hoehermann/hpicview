/***************************************************************
 * Name:      hpicviewMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Hermann Höhne (hermann@hehoe.de)
 * Created:   2018-03-31
 * Copyright: Hermann Höhne (www.hehoe.de)
 * License:
 **************************************************************/

// TODO: enable global exceptions
// TODO: regsiter accelerators without ctrl

#include "hpicviewMain.h"
#include <wx/msgdlg.h>

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


hpicviewFrame::hpicviewFrame(wxFrame *frame)
    : GUIFrame(frame)
{
#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_("Hello Code::Blocks user!"), 0);
    statusBar->SetStatusText(wxbuildinfo(short_f), 1);
#endif
}

hpicviewFrame::~hpicviewFrame()
{
}

void hpicviewFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void hpicviewFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void hpicviewFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("About hpicview"));
}

#include <wx/filedlg.h>

void hpicviewFrame::OnFileOpen(wxCommandEvent& event) {
	wxFileDialog openFileDialog(
        this, _("Open file"), "", "",
        "JPEG files|*.jpg;*.jpeg|"
        "All files|*.*",
        wxFD_OPEN, wxDefaultPosition
    );
	if (openFileDialog.ShowModal() == wxID_OK) {
        OpenFile(openFileDialog.GetPath());
	}
}

void hpicviewFrame::OnRotateRight(wxCommandEvent& event) {
    try {
        // TODO: check if image loaded at all
        jpegdata = jpegtran.rotate_right(jpegdata);
        SetJPEG(jpegdata);
    } catch (std::exception & ex) {
        wxMessageBox(ex.what(), _("Unable to perform"));
    }
}

void hpicviewFrame::OnRotateLeft(wxCommandEvent& event) {
    try {
        // TODO: check if image loaded at all
        jpegdata = jpegtran.rotate_left(jpegdata);
        SetJPEG(jpegdata);
    } catch (std::exception & ex) {
        wxMessageBox(ex.what(), _("Unable to perform"));
    }
}

//#include <boost/interprocess/file_mapping.hpp>
//#include <boost/interprocess/mapped_region.hpp>

void hpicviewFrame::OpenFile(wxString filename) {
    try {
        jpegdata = get_file_contents(filename);
        //boost::interprocess::file_mapping m_file(filename, boost::interprocess::read_only);
        //boost::interprocess::mapped_region region(m_file, boost::interprocess::read_only);
        // keeping the file memory mapped is probably annoying as it locks the file on windows
        //SetJPEG((unsigned char*)region.get_address(), region.get_size());
        SetJPEG(jpegdata);
    } catch(std::exception & ex) {
        wxMessageBox(ex.what(), _("Unable to open image file"));
    }
    Layout();
}

#include <wx/mstream.h>

void hpicviewFrame::SetJPEG(const std::string & jpegdata) {
    /* from https://forums.wxwidgets.org/viewtopic.php?t=18325 */
    wxMemoryInputStream jpegStream(
        (unsigned char *)jpegdata.c_str(),
        jpegdata.size()
    );
    wxImage jpegImage;
    jpegImage.LoadFile(jpegStream, wxBITMAP_TYPE_JPEG);
    wxBitmap b(jpegImage);
    m_bitmap->SetBitmap(b);
}

#include <fstream>
#include <cerrno>

/* from https://insanecoding.blogspot.de/2011/11/how-to-read-in-file-in-c.html */
std::string hpicviewFrame::get_file_contents(wxString filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}
