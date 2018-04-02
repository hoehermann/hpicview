/***************************************************************
 * Name:      hpicviewMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Hermann Höhne (hermann@hehoe.de)
 * Created:   2018-03-31
 * Copyright: Hermann Höhne (www.hehoe.de)
 * License:
 **************************************************************/

// TODO: open file from path given by command-line
// TODO: folder navigation (with background scan)
// TODO: enable global exceptions
// TODO: regsiter accelerators without ctrl
// TODO: transform thumbnail, too

#include "hpicviewMain.h"
#include <wx/msgdlg.h>

//helper functions
#include <fstream>
#include <cerrno>

std::string get_file_contents(const std::string & filename)
{
    /* from https://insanecoding.blogspot.de/2011/11/how-to-read-in-file-in-c.html */
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in) {
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
    : GUIFrame(frame), dirty(false)
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
    msg += "\n\nContains icons by fontawesome.";
    wxMessageBox(msg, _("About hpicview"));
}

#include <wx/filedlg.h>

void hpicviewFrame::OnOpen(wxCommandEvent& event) {
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
        jpegdata = JPEGtran::rotate_right(jpegdata);
        dirty = true;
        SetJPEG(jpegdata);
        WriteIfDirty(); // TODO: write on close / switch file / explicit request only
    } catch (std::exception & ex) {
        wxMessageBox(ex.what(), _("Unable to perform"));
    }
}

void hpicviewFrame::OnRotateLeft(wxCommandEvent& event) {
    try {
        jpegdata = JPEGtran::rotate_left(jpegdata);
        dirty = true;
        SetJPEG(jpegdata);
        WriteIfDirty(); // TODO: write on close / switch file / explicit request only
    } catch (std::exception & ex) {
        wxMessageBox(ex.what(), _("Unable to perform"));
    }
}

void hpicviewFrame::OpenFile(const wxString & filename) {
    try {
        this->filename = "";
        auto path = boost::filesystem::path(filename);
        this->jpegdata = get_file_contents(std::string(filename));
        SetJPEG(jpegdata);
        this->modification_date =
            boost::filesystem::last_write_time(path);
        this->filename = filename;

        boost::filesystem::directory_iterator directory_iterator =
            boost::filesystem::directory_iterator(path.parent_path());
        filenames_images.clear();
        std::copy_if(
            directory_iterator, {},
            std::back_inserter(filenames_images),
            [](const boost::filesystem::path & p){return p.extension() == ".jpg";}
        ); // TODO: check against list of allowed extensions, ignore case
        std::sort(filenames_images.begin(), filenames_images.end());
        filenames_position = find(filenames_images.begin(), filenames_images.end(), path);
        ptrdiff_t pos = std::distance(filenames_images.begin(), filenames_position);
        SetStatusText(wxString::Format(wxT("%ld/%ld"),pos+1,filenames_images.size()), 1);

        Layout();
    } catch(std::exception & ex) {
        wxMessageBox(ex.what(), _("Unable to open image file"));
    }
}

void hpicviewFrame::WriteIfDirty() {
    if (dirty) {
        Write(this->filename);
        boost::filesystem::last_write_time(
            boost::filesystem::path(this->filename),
            this->modification_date
        );
    }
}

#include <fstream>

void hpicviewFrame::Write(const wxString & filename) {
    if (!jpegdata.size()) {
        throw std::runtime_error("Tried to write empty file. This should never happen.");
    }
    dirty = false;
    auto f = std::fstream(filename, std::ios::out | std::ios::binary);
    f.write(jpegdata.c_str(), jpegdata.size());
    f.close();
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
