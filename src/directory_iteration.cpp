#include "hpicviewMain.hpp"

void hpicviewFrame::OnPrevious(wxCommandEvent&) {
    if (!filenames_images.empty() && filenames_position != filenames_images.begin()) {
        auto it = std::prev(filenames_position);
        OpenFile(std_string_to_wxString(it->string()));
        SetFileIndex(it);
    }
}

void hpicviewFrame::OnNext(wxCommandEvent&) {
    if (!filenames_images.empty()) {
        auto it = std::next(filenames_position);
        if (it != filenames_images.end()) {
            OpenFile(std_string_to_wxString(it->string()));
            SetFileIndex(it);
        }
    }
}

void hpicviewFrame::OnDelete(wxCommandEvent&) {
    if (!this->m_filename.empty()) {
        //assert(filenames_images.empty());
        boost::filesystem::remove(this->m_filename); // remove current file from disk
        ptrdiff_t pos = std::distance(filenames_images.begin(), filenames_position); // get position of just deleted file
        if (pos < filenames_images.size() - 1) { // there is a file after the just deleted one
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

std::vector<boost::filesystem::path>::iterator
hpicviewFrame::UpdateDirectoryListing(
        boost::filesystem::path path
) {
    boost::filesystem::path directory;
    if (boost::filesystem::is_directory(path)) {
        directory = path;
        path.clear(); // clear path to signalize "no file was opened"
    } else {
        directory = path.parent_path();
    }
    boost::filesystem::directory_iterator directory_iterator = boost::filesystem::directory_iterator(directory);
    filenames_images.clear();
    std::copy_if(
        directory_iterator, {},
        std::back_inserter(filenames_images),
        [this](const boost::filesystem::path & p){
            return this->m_image_extensions.count(std_string_to_wxString(p.extension().string()).Lower());
        }
    );
    if (filenames_images.empty()) {
        return filenames_images.end();
    }
    std::sort(filenames_images.begin(), filenames_images.end());
    if (path.empty()) {
        // no file was opened, provide first file in list
        // TODO: do not fail critically if list is empty
        path = *filenames_images.begin();
    }
    return find(filenames_images.begin(), filenames_images.end(), path);
}

void hpicviewFrame::SetFileIndex(const std::vector<boost::filesystem::path>::iterator & p) {
    this->filenames_position = p;
    ptrdiff_t pos = std::distance(filenames_images.begin(), filenames_position);
    SetStatusText(wxString::Format(
        wxT("%u/%u"),
        (unsigned int)(pos+1),
        (unsigned int)(filenames_images.size())
    ), STATUSBAR_COLUMN_INDEX);
}
