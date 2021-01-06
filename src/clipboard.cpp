#include "hpicviewMain.hpp"
#include <wx/clipbrd.h>

// based on https://forums.wxwidgets.org/viewtopic.php?t=19643
void hpicviewFrame::CopyToClipboard() {
    if (!wxTheClipboard->IsOpened() && !wxTheClipboard->Open()) {
        throw std::runtime_error("Could not access the clipboard.");
    }
    if (m_image.IsOk()) {
        this->Enable(false);
        bool ok = wxTheClipboard->AddData(new wxBitmapDataObject(bitmap->GetBitmap()));
        this->Enable(true);
        if (!ok) {
            throw std::runtime_error("Copying to clipboard has failed.");
        }
    }
}
