/***************************************************************
 * Name:      hpicviewMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Hermann Höhne (hermann@hehoe.de)
 * Created:   2018-03-31
 * Copyright: Hermann Höhne (www.hehoe.de)
 * License:
 **************************************************************/

// TODO: try to open all images (get all available image handlers, query their extensions; check against /list/ of allowed extensions, ignore case in directory iterator; offer rotation only for JPEG)
// TODO: reset exif orientation flag after rotate
// TODO: transform thumbnail, too
// TODO: enable global exceptions
// TODO: scan folder in background

#include "hpicviewMain.h"
#include <wx/msgdlg.h>

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
    SetStatusText(_("No image."), 0);
    SetStatusText(wxbuildinfo(short_f), 1);
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

void hpicviewFrame::OnAbout(wxCommandEvent&)
{
    wxString msg;
    msg << "hpicview Version " << VERSION << "\n\n";
    msg << "Built with " << wxbuildinfo(long_f) << "\n\n";
    msg << "Contains icons by fontawesome.";
    wxMessageBox(msg, _("About hpicview"));
}

#include <wx/filedlg.h>

void hpicviewFrame::OnOpen(wxCommandEvent&) {
	wxFileDialog openFileDialog(
        this, _("Open file"), "", "",
        "JPEG files|*.jpg;*.jpeg|"
        "All files|*.*",
        wxFD_OPEN, wxDefaultPosition
    );
	if (openFileDialog.ShowModal() == wxID_OK) {
        try {
            OpenFile(openFileDialog.GetPath());
        } catch(std::exception & ex) {
            wxMessageBox(ex.what(), _("Unable to open image file"));
        }
    }
}

void hpicviewFrame::OnRotateRight(wxCommandEvent&) {
    try {
        jpegdata = JPEGtran::rotate_right(jpegdata);
        dirty = true;
        SetJPEG(jpegdata);
        WriteIfDirty(); // TODO: write on close / switch file / explicit request only
    } catch (std::exception & ex) {
        wxMessageBox(ex.what(), _("Unable to perform"));
    }
}

void hpicviewFrame::OnRotateLeft(wxCommandEvent&) {
    try {
        jpegdata = JPEGtran::rotate_left(jpegdata);
        dirty = true;
        SetJPEG(jpegdata);
        WriteIfDirty(); // TODO: write on close / switch file / explicit request only
    } catch (std::exception & ex) {
        wxMessageBox(ex.what(), _("Unable to perform"));
    }
}

std::vector<boost::filesystem::path>::iterator
hpicviewFrame::UpdateDirectoryListing(
        const boost::filesystem::path & path
) {
    boost::filesystem::directory_iterator directory_iterator =
        boost::filesystem::directory_iterator(path.parent_path());
    filenames_images.clear();
    std::copy_if(
        directory_iterator, {},
        std::back_inserter(filenames_images),
        [](const boost::filesystem::path & p){return p.extension() == ".jpg";}
    );
    std::sort(filenames_images.begin(), filenames_images.end());
    return find(filenames_images.begin(), filenames_images.end(), path);
}

void hpicviewFrame::OpenFile(const wxString & filename) {
    this->jpegdata = get_file_contents(std::string(filename));
    SetJPEG(jpegdata);
    boost::filesystem::path path(filename);
    path = boost::filesystem::canonical(path);
    this->modification_date =
        boost::filesystem::last_write_time(path);
    bool directory_has_changed = this->filename.empty() || this->filename.parent_path() != path.parent_path();
    this->filename = path;

    SetTitle(wxString::Format(wxT("hpicview - %s"),path.filename().c_str()));
    SetStatusText(wxString::Format(wxT("Loaded %s."),path.filename().c_str()),0);
    if (directory_has_changed) {
        std::vector<boost::filesystem::path>::iterator p = UpdateDirectoryListing(path);
        SetPosition(p);
    }
    Layout();
}

void hpicviewFrame::SetPosition(const std::vector<boost::filesystem::path>::iterator & p) {
    this->filenames_position = p;
    ptrdiff_t pos = std::distance(filenames_images.begin(), filenames_position);
    SetStatusText(wxString::Format(wxT("%ld/%ld"),pos+1,filenames_images.size()), 1);
}

void hpicviewFrame::WriteIfDirty() {
    if (dirty) {
        Write(wxString(this->filename.c_str()));
        boost::filesystem::last_write_time(
            boost::filesystem::path(this->filename),
            this->modification_date
        );
    }
}

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

void hpicviewFrame::OnPrevious(wxCommandEvent&) {
    if (!filenames_images.empty()) {
        auto it = std::prev(filenames_position);
        if (it != filenames_images.begin()-1) {
            OpenFile(wxString(it->c_str()));
            SetPosition(it);
        }
    }
}

void hpicviewFrame::OnNext(wxCommandEvent&) {
    if (!filenames_images.empty()) {
        auto it = std::next(filenames_position);
        if (it != filenames_images.end()) {
            OpenFile(wxString(it->c_str()));
            SetPosition(it);
        }
    }
}
