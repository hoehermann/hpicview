#include <wx/msgdlg.h>
#include "hpicviewMain.hpp"
#include "extensions.hpp"

enum wxbuildinfoformat {
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode");
#else
    #error This assumes a UTF-8 enabled system. Must build with unicode support.
		// String conversions heavily rely on UTF8
        wxbuild << _T("-ANSI");
#endif
    }

    return wxbuild;
}

void hpicviewFrame::OnAbout(wxCommandEvent&)
{
    wxString msg;
#ifndef VERSION
    #define VERSION ""
#endif
    msg << "hpicview " << VERSION << "\n\n";
    msg << "GPL-3.0 License\n\n";
    msg << "Built with " << wxbuildinfo(long_f) << ".\n\n";
    msg << "Contains icons by fontawesome.\n\n";
    msg << "Default extensions of built-in image formats:\n" << GetImageExtWildcard(GetImageExts(false)) << "\n\n";
	msg << "https://github.com/hoehermann/hpicview" << "\n";
    wxMessageBox(msg, wxT("About hpicview"));
}