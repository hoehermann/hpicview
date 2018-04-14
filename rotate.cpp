#include "hpicviewMain.h"

#include <wx/msgdlg.h>

void hpicviewFrame::OnRotateRight(wxCommandEvent&) {
    try {
        if (!m_image.IsOk() || m_image.GetType() !=  wxBITMAP_TYPE_JPEG) {
            throw std::runtime_error("No JPEG loaded.");
        }
        m_imagedata = JPEGtran::rotate_right(m_imagedata);
        m_dirty = true;
        SetImageData(m_imagedata);
        FitAndDisplay();
        WriteIfDirty(); // TODO: write on close / switch file / explicit request only
    } catch (std::exception & ex) {
        wxMessageBox(ex.what(), _("Unable to perform"));
    }
}

void hpicviewFrame::OnRotateLeft(wxCommandEvent&) {
    try {
        if (!m_image.IsOk() || m_image.GetType() !=  wxBITMAP_TYPE_JPEG) {
            throw std::runtime_error("No JPEG loaded.");
        }
        m_imagedata = JPEGtran::rotate_left(m_imagedata);
        m_dirty = true;
        SetImageData(m_imagedata);
        FitAndDisplay();
        WriteIfDirty(); // TODO: write on close / switch file / explicit request only
    } catch (std::exception & ex) {
        wxMessageBox(ex.what(), _("Unable to perform"));
    }
}
