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
    short_f, long_f
};

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
    : GUIFrame(frame), m_dirty(false), m_image_extensions(GetImageExts())
{
    SetStatusText(_("No image."), STATUSBAR_COLUMN_MAIN);
    SetStatusText(wxbuildinfo(short_f), STATUSBAR_COLUMN_INDEX);
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

#include <wx/msgdlg.h>

void hpicviewFrame::OnAbout(wxCommandEvent&)
{
    wxString msg;
#ifndef VERSION
    #define VERSION "unknown"
#endif
    msg << "hpicview Version " << VERSION << "\n\n";
    msg << "Built with " << wxbuildinfo(long_f) << "\n\n";
    msg << "Contains icons by fontawesome.\n\n";
    msg << "Built-in image format extensions:\n" << GetImageExtWildcard(m_image_extensions);
    wxMessageBox(msg, _("About hpicview"));
}

#include <wx/filedlg.h>

void hpicviewFrame::OnOpen(wxCommandEvent&) {
    wxString exts("All built-in image files|");
    exts << GetImageExtWildcard(m_image_extensions);
    exts << "|";

	wxFileDialog openFileDialog(
        this, _("Open file"), "", "",
        "JPEG files|*.jpg;*.jpeg;*.JPG|"
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

void hpicviewFrame::OpenFile(const wxString & filename) {
    this->m_imagedata = get_file_contents(std::string(filename));
    SetImageData(m_imagedata);
    boost::filesystem::path path(filename);
    path = boost::filesystem::canonical(path);
    this->m_modification_date =
        boost::filesystem::last_write_time(path);
    bool directory_has_changed = this->m_filename.empty() || this->m_filename.parent_path() != path.parent_path();
    this->m_filename = path;

    SetTitle(wxString::Format(wxT("hpicview - %s"),path.filename().c_str()));
    SetStatusText(wxString::Format(wxT("Loaded %s"),path.filename().c_str()), STATUSBAR_COLUMN_MAIN);
    if (directory_has_changed) {
        std::vector<boost::filesystem::path>::iterator p = UpdateDirectoryListing(path);
        SetFileIndex(p);
    }
    FitAndDisplay();
}

void hpicviewFrame::WriteIfDirty() {
    if (m_dirty) {
        Write(wxString(this->m_filename.c_str()));
        boost::filesystem::last_write_time(
            boost::filesystem::path(this->m_filename),
            this->m_modification_date
        );
    }
}

void hpicviewFrame::Write(const wxString & filename) {
    if (this->m_imagedata.empty()) {
        throw std::runtime_error("Tried to write empty file. This should never happen.");
    }
    this->m_dirty = false;
    auto f = std::fstream(filename, std::ios::out | std::ios::binary);
    f.write(this->m_imagedata.c_str(), this->m_imagedata.size());
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
}

void hpicviewFrame::SetConfiguration() {
    this->toolBar->ToggleTool(
        this->toolZoomFitAuto->GetId(),
        true); // TODO: make configurable
}

