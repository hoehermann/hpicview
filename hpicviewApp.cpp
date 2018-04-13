/***************************************************************
 * Name:      hpicviewApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Hermann Höhne (hermann@hehoe.de)
 * Created:   2018-03-31
 * Copyright: Hermann Höhne (www.hehoe.de)
 * License:
 **************************************************************/

#include "hpicviewApp.h"

IMPLEMENT_APP(hpicviewApp);

bool hpicviewApp::OnInit() {
    /* from https://forums.wxwidgets.org/viewtopic.php?t=21065 */
    wxInitAllImageHandlers();

    this->frame = new hpicviewFrame(0L);

    // TODO: use wxCmdLineParser, treat first positional argument as filename
    if (this->argc == 2) {
        this->frame->OpenFile(this->argv[1]);
    }

    this->frame->Show();

    Bind(wxEVT_CHAR_HOOK, &hpicviewApp::OnCharHook, this);

    return true;
}

int hpicviewApp::OnExit() {
    Unbind(wxEVT_CHAR_HOOK, &hpicviewApp::OnCharHook, this);
    return 0;
}

/* from http://blog.pcitron.fr/2012/09/11/application-wide-shortcuts-with-wxwidgets-on-windows/ */
void hpicviewApp::OnCharHook(wxKeyEvent& event) {
    if (event.ControlDown()) {
        // do not swallow "real" shortcuts (with ctrl pressed)
        event.Skip();
    } else {
        wxCommandEvent ce(wxEVT_NULL, 0);
        switch (event.GetKeyCode()) {
            case 'R':
                this->frame->OnRotateRight(ce);
            break;
            case 'L':
                this->frame->OnRotateLeft(ce);
            break;
            case WXK_LEFT:
                this->frame->OnPrevious(ce);
            break;
            case WXK_RIGHT:
                this->frame->OnNext(ce);
            break;
            case WXK_ESCAPE :
                this->frame->OnQuit(ce);
            break;
            default:
                //std::cerr << "Unbound key:" << event.GetUnicodeKey() << std::endl;
                event.Skip();
            break;
        }
    }
}

