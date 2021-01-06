#include <fstream>
//#include <cerrno>
#include <wx/mstream.h>

#include "extensions.hpp"
#include "hpicviewMain.hpp"

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

void hpicviewFrame::SetImageData(const std::string & imagedata) {
    /* from https://forums.wxwidgets.org/viewtopic.php?t=18325 */
    wxMemoryInputStream imagedataStream(
        (unsigned char *)imagedata.c_str(),
        imagedata.size()
    );
    m_image.LoadFile(imagedataStream);
}

void hpicviewFrame::OnDelete(wxCommandEvent&) {
    if (!this->m_filename.empty()) {
        //assert(filenames_images.empty());
        boost::filesystem::remove(this->m_filename); // remove current file from disk
        ptrdiff_t pos = std::distance(filenames_images.begin(), filenames_position); // get position of just deleted file
        if (pos < ptrdiff_t(filenames_images.size() - 1)) { // there is a file after the just deleted one
            auto next = filenames_images.begin() + pos + 1;
            OpenFile(std_string_to_wxString(next->string())); // open next file
        } else { // was at the end
            pos--; // list is now shorter
            if (pos >= 0) { // there is a file before the just deleted one
                auto previous = filenames_images.begin() + pos;
                OpenFile(std_string_to_wxString(previous->string())); // open previous file
            }
        }
        filenames_images.erase(filenames_position); // remove just deleted file from directory list
        SetFileIndex(filenames_images.begin() + pos); // update iterator (still points to the current position, now another file)
        if (filenames_images.empty()) {
            SetStatusText(
                wxT("The file has been deleted. No more files remain in directory."), 
                STATUSBAR_COLUMN_MAIN
            );
        }
    }
}