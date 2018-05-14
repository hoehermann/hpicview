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
    if (!m_image.IsOk()) {
        return;
    }
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
    this->bitmap->SetBitmap(wxBitmap(scaledImage));
    Layout();
}

void hpicviewFrame::ZoomFit() {
    if (!m_image.IsOk()) {
        return;
    }
    float image_width = m_image.GetWidth();
    float image_height = m_image.GetHeight();
    const wxSize & client_size = this->GetClientSize(); // this uses the main frame's client size instead of mainScrolledWindow's client size (relies on scrollbars being hidden automatically)
    float client_width = client_size.GetWidth();
    float client_height = client_size.GetHeight();
    float smaller_factor =
        std::min(client_height/image_height, client_width/image_width);
    int fit_zoom_exponent = std::floor(std::log2(smaller_factor));
    ScaleImage(fit_zoom_exponent);
}

void hpicviewFrame::OnZoomFit(wxCommandEvent&) {
    ZoomFit();
}

void hpicviewFrame::OnZoomOut(wxCommandEvent&) {
    try {
        ScaleImage(this->m_view_zoom_exponent-1);
    } catch(std::exception & ex) {
        wxMessageBox(ex.what(), _("Unable to perform"));
    }
}

void hpicviewFrame::OnZoomIn(wxCommandEvent&) {
    ScaleImage(this->m_view_zoom_exponent+1);
}

void hpicviewFrame::FitAndDisplay() {
    if (this->menuViewZoomFitAuto->IsChecked()) {
        ZoomFit();
    } else {
        SetViewZoomExponent(0);
        this->bitmap->SetBitmap(wxBitmap(m_image));
    }
}
