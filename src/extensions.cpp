#include "extensions.hpp"

#include <wx/wx.h>

// based on wxString wxImage::GetImageExtWildcard() from src/common/image.cpp
std::set<wxString> GetImageExts(bool include_alternatives)
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
