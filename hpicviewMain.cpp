/***************************************************************
 * Name:      hpicviewMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Hermann Höhne (hermann@hehoe.de)
 * Created:   2018-03-31
 * Copyright: Hermann Höhne (www.hehoe.de)
 * License:
 **************************************************************/

// TODO: try to open all images (get all available image handlers, query their extensions; check against /list/ of allowed extensions, ignore case in directory iterator; offer rotation only for JPEG)
// TODO: fullscreen mode
// TODO: scaling
// TODO: reset exif orientation flag after rotate
// TODO: transform thumbnail, too
// TODO: enable global exceptions
// TODO: scan folder in background
// TODO: build application against the same libjpeg as wxwidgets

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

#include <iostream>

// based on wxString wxImage::GetImageExtWildcard() from src/common/image.cpp
std::set<wxString> GetImageExts()
{
    std::set<wxString> exts;
    wxList& Handlers = wxImage::GetHandlers();
    for (const auto & o : Handlers) {
        wxImageHandler* Handler = (wxImageHandler*)o;
        exts.insert(wxString("."+Handler->GetExtension()));
        for (const auto & e : Handler->GetAltExtensions()) {
            exts.insert(wxString("."+e));
        }
    }
    return exts;
}


hpicviewFrame::hpicviewFrame(wxFrame *frame)
    : GUIFrame(frame), dirty(false), image_extensions(GetImageExts())
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

wxString GetImageExtWildcard(std::set<wxString> image_extensions){
    wxString exts;
    bool first = true;
    for(const auto & e : image_extensions) {
        if (first) {
            first = false;
        } else {
            exts << ";";
        }
        exts << "*" << e;
    }
    return exts;
}

void hpicviewFrame::OnAbout(wxCommandEvent&)
{
    wxString msg;
#ifndef VERSION
    #define VERSION "unknown"
#endif
    msg << "hpicview Version " << VERSION << "\n\n";
    msg << "Built with " << wxbuildinfo(long_f) << "\n\n";
    msg << "Contains icons by fontawesome.\n\n";
    msg << "Built-in image format extensions:\n" << GetImageExtWildcard(image_extensions);
    wxMessageBox(msg, _("About hpicview"));
}

#include <wx/filedlg.h>

void hpicviewFrame::OnOpen(wxCommandEvent&) {
    wxString exts("All built-in image files|");
    exts << GetImageExtWildcard(image_extensions);
    exts << "|";

	wxFileDialog openFileDialog(
        this, _("Open file"), "", "",
        "JPEG files|*.jpg;*.jpeg|"
        + exts +
        // "All built-in image files "+wxImage::GetImageExtWildcard()+"|"
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
        if (m_image.GetType() !=  wxBITMAP_TYPE_JPEG) {
            throw std::runtime_error("No JPEG loaded.");
        }
        imagedata = JPEGtran::rotate_right(imagedata);
        dirty = true;
        SetImageData(imagedata);
        WriteIfDirty(); // TODO: write on close / switch file / explicit request only
    } catch (std::exception & ex) {
        wxMessageBox(ex.what(), _("Unable to perform"));
    }
}

void hpicviewFrame::OnRotateLeft(wxCommandEvent&) {
    try {
        if (m_image.GetType() !=  wxBITMAP_TYPE_JPEG) {
            throw std::runtime_error("No JPEG loaded.");
        }
        imagedata = JPEGtran::rotate_left(imagedata);
        dirty = true;
        SetImageData(imagedata);
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
        [this](const boost::filesystem::path & p){
            return this->image_extensions.count(wxString(p.extension().c_str()).Lower());
        }
    );
    std::sort(filenames_images.begin(), filenames_images.end());
    return find(filenames_images.begin(), filenames_images.end(), path);
}

void hpicviewFrame::OpenFile(const wxString & filename) {
    this->imagedata = get_file_contents(std::string(filename));
    SetImageData(imagedata);
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
    if (imagedata.empty()) {
        throw std::runtime_error("Tried to write empty file. This should never happen.");
    }
    dirty = false;
    auto f = std::fstream(filename, std::ios::out | std::ios::binary);
    f.write(imagedata.c_str(), imagedata.size());
    f.close();
}

#include <wx/mstream.h>

void hpicviewFrame::SetImageData(const std::string & imagedata) {
    /* from https://forums.wxwidgets.org/viewtopic.php?t=18325 */
    wxMemoryInputStream imagedataStream(
        (unsigned char *)imagedata.c_str(),
        imagedata.size()
    );
    m_image.LoadFile(imagedataStream);
    m_bitmap->SetBitmap(wxBitmap(m_image));
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
