#include "hpicviewMain.hpp"
#include <wx/clipbrd.h>

// based on https://forums.wxwidgets.org/viewtopic.php?t=19643
void hpicviewFrame::CopyToClipboard() {
    if (!wxTheClipboard->IsOpened() && !wxTheClipboard->Open()) {
        SetStatusText(
            wxT("Could not access the clipboard."), 
            STATUSBAR_COLUMN_MAIN
        );
        return;
    }
    if (m_image.IsOk()) {
        this->Enable(false);
        SetStatusText(
            wxT("Copying image to clipboard…"), 
            STATUSBAR_COLUMN_MAIN
        );
        if (!wxTheClipboard->AddData(new wxBitmapDataObject(wxBitmap(m_image)))) {
            SetStatusText(
                wxT("Copying to clipboard has failed."), 
                STATUSBAR_COLUMN_MAIN
            );
        } else {
            SetStatusText(
                wxT("Copying to clipboard has completed."), 
                STATUSBAR_COLUMN_MAIN
            );
        }
        this->Enable(true);
    }
}
