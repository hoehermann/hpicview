#include "hpicviewMain.h"

#include <cmath>
#include <wx/msgdlg.h>

void hpicviewFrame::SetViewZoomExponent(int view_zoom_exponent) {
    this->m_view_zoom_exponent = view_zoom_exponent;
    float view_zoom_factor = std::pow(2, m_view_zoom_exponent);
    float zoom_percent = 100.0f*view_zoom_factor;
    SetStatusText(wxString::Format(wxT("%.2f%%"),zoom_percent), STATUSBAR_COLUMN_ZOOM);
}

void hpicviewFrame::ScaleImage(int view_zoom_exponent) {
    int width = m_image.GetWidth();
    int height = m_image.GetHeight();
    float view_zoom_factor = std::pow(2, view_zoom_exponent);
    width = int(float(width)*view_zoom_factor);
    height = int(float(height)*view_zoom_factor);
    if (width <= 0 || height <= 0) {
        throw std::runtime_error("Cannot scale any smaller.");
    }
    SetViewZoomExponent(view_zoom_exponent);
    wxImage scaledImage = m_image.Scale(width, height, wxIMAGE_QUALITY_NEAREST);
    this->m_bitmap->SetBitmap(wxBitmap(scaledImage));
    Layout();
}

void hpicviewFrame::OnZoomOut(wxCommandEvent&) {
    try {
        ScaleImage(this->m_view_zoom_exponent-1);
    } catch(std::exception & ex) {
        wxMessageBox(ex.what(), _("Unable to perform"));
    }
}

void hpicviewFrame::OnZoomIn(wxCommandEvent&) {
    try {
        ScaleImage(this->m_view_zoom_exponent+1);
    } catch(std::exception & ex) {
        wxMessageBox(ex.what(), _("Unable to perform"));
    }
}
