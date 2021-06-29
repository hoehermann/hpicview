#include "hpicviewMain.hpp"
#include <wx/clipbrd.h>

// based on https://forums.wxwidgets.org/viewtopic.php?t=19643
void hpicviewFrame::CopyToClipboard() {
    if (!wxTheClipboard->IsOpened() && !wxTheClipboard->Open()) {
        throw std::runtime_error("Could not access the clipboard.");
    }
    if (m_image.IsOk()) {
        bool ok = false;
        //this->Enable(false); // this seems to mess up OnCharHook :/
        // TODO: keep original image, set display scaling for accurate selection and copying from m_image
        const wxBitmap & bm = bitmap->GetBitmap();
        if (bitmap->HasSelection()) {
            wxRect bmrect(wxPoint(0,0), bm.GetSize());
            wxRect selection = bitmap->GetSelection();
            wxASSERT(bmrect.Contains(selection));
            ok = wxTheClipboard->SetData(new wxBitmapDataObject(bm.GetSubBitmap(selection)));
        } else {
            ok = wxTheClipboard->SetData(new wxBitmapDataObject(bm));
        }
        //this->Enable(true);
        if (!ok) {
            throw std::runtime_error("Copying to clipboard has failed.");
        }
    }
    wxTheClipboard->Close();
}
