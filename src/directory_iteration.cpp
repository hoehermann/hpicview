#include "hpicviewMain.hpp"

void hpicviewFrame::OnPrevious(wxCommandEvent&) {
    if (!filenames_images.empty()) {
        auto it = std::prev(filenames_position);
        if (it != filenames_images.begin()-1) {
            OpenFile(std_string_to_wxString(it->string()));
            SetFileIndex(it);
        }
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
            return this->m_image_extensions.count(std_string_to_wxString(p.extension().string()).Lower());
        }
    );
    std::sort(filenames_images.begin(), filenames_images.end());
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
