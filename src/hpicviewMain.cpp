/***************************************************************
 * Name:      hpicviewMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Hermann Höhne (hermann@hehoe.de)
 * Created:   2018-03-31
 * Copyright: Hermann Höhne (www.hehoe.de)
 * License:   GNU GPLv3
 **************************************************************/

#include "hpicviewMain.hpp"
#include "droptarget.hpp"

#include <fstream>
#include <cerrno>

std::string wxString_to_std_string(const wxString & wxstring) {
    // TODO: look for a sane solution
    // maybe see https://stackoverflow.com/questions/28147826/converting-stl-unicode-string-to-wxstring-gives-empty-string
    // I saw https://www.wxwidgets.org/blog/2020/08/implicit_explicit_encoding/. Oh no.
    // https://docs.wxwidgets.org/trunk/classwx_string.html helped
    #if defined(__WXMSW__)
    return wxstring.ToStdString(); // works on Windows
    #else
    return std::string(wxstring.ToUTF8()); // works on Linux
    #endif
}

wxString std_string_to_wxString(const std::string & stdstring) {
    // TODO: see wxString_to_std_string
    #if defined(__WXMSW__)
    return wxString(stdstring);
    #else
    return wxString::FromUTF8(static_cast<const char *>(stdstring.c_str()), static_cast<size_t>(stdstring.size())); // works on Linux
    #endif
}

std::string get_file_contents(const std::string & filename)
{
    /* from https://insanecoding.blogspot.de/2011/11/how-to-read-in-file-in-c.html */
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in.good()) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    } else {
        throw std::runtime_error("Could not load file.");
    }
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
    #error This assumes a UTF-8 enabled system. Must build with unicode support.
    // String conversions heavily rely on UTF8
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


// based on wxString wxImage::GetImageExtWildcard() from src/common/image.cpp
std::set<wxString> GetImageExts(bool include_alternatives = true)
{
    std::set<wxString> exts;
    wxList& Handlers = wxImage::GetHandlers();
    for (const auto & o : Handlers) {
        wxImageHandler* Handler = (wxImageHandler*)o;
        exts.insert(wxString("."+Handler->GetExtension()));
        if (include_alternatives) {
            for (const auto & e : Handler->GetAltExtensions()) {
                exts.insert(wxString("."+e));
            }
        }
    }
    return exts;
}

#include "../resources/icon.svg.xpm"

hpicviewFrame::hpicviewFrame(wxFrame *frame)
    : GUIFrame(frame), m_dirty(false), m_image_extensions(GetImageExts())
{
    this->SetIcon(wxIcon(icon_svg_xpm));
    const int status_widths[] = {-70,-20,-10};
    this->SetStatusWidths(3, status_widths);
    this->SetStatusText(_("No image."), STATUSBAR_COLUMN_MAIN);
    this->SetStatusText(wxbuildinfo(short_f), STATUSBAR_COLUMN_INDEX);
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
    msg << "Default extensions of built-in image formats:\n" << GetImageExtWildcard(GetImageExts(false));
    wxMessageBox(msg, _("About hpicview"));
}

#include <wx/filedlg.h>

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
        try {
            OpenFile(openFileDialog.GetPath());
        } catch(std::exception & ex) {
            wxMessageBox(ex.what(), _("Unable to open image file"));
        }
    }
}

#include <iostream>

void hpicviewFrame::OpenPath(const wxString & pathname) {
    boost::filesystem::path path(wxString_to_std_string(pathname));
    if (boost::filesystem::is_directory(path)) {
        const auto p = UpdateDirectoryListing(path);
        // TODO: restructure. this looks ugly. validity of p should not be checked by checking filenames_images.empty()
        if (!filenames_images.empty()) {
            //this->m_filename = *p; // setting file-name before image is actually loaded. unsure if this is a good idea since this->m_filename.empty() is a shorthand for "file was loaded"
            this->OpenFile(std_string_to_wxString(p->string()));
        }
    } else {
        this->OpenFile(pathname);
    }
}

void hpicviewFrame::OpenFile(const wxString & filename) {
    std::string stdstring_filename(wxString_to_std_string(filename));
    this->m_imagedata = get_file_contents(stdstring_filename);
    SetImageData(m_imagedata);
    boost::filesystem::path path(stdstring_filename);
    //path = boost::filesystem::canonical(path); // TODO: check how to get parent in case of file name supplied only
    this->m_modification_date = boost::filesystem::last_write_time(path);
    bool directory_has_changed = this->m_filename.empty() || this->m_filename.parent_path() != path.parent_path();
    this->m_filename = path;

    SetTitle(wxString::Format(wxT("hpicview - %s"),path.filename().c_str()));
    unsigned long int image_size_memory_kB = this->m_image.GetWidth()*this->m_image.GetHeight()*(this->m_image.HasAlpha()?4:3)/1024; /* according to https://forums.wxwidgets.org/viewtopic.php?t=42790 */
    unsigned long int image_size_disk_kB = this->m_imagedata.size()/1024;
    SetStatusText(
        wxString::Format(
            wxT("Loaded %s (%lu kB in memory, %lu kB on disk)"),
            std_string_to_wxString(path.filename().string()),
            image_size_memory_kB,
            image_size_disk_kB
        ),
        STATUSBAR_COLUMN_MAIN
    );
    if (directory_has_changed) {
        const std::vector<boost::filesystem::path>::iterator p = UpdateDirectoryListing(path);
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
    auto f = std::fstream(wxString_to_std_string(filename), std::ios::out | std::ios::binary);
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
