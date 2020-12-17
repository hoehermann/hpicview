/***************************************************************
 * Name:      hpicviewApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Hermann Höhne (hermann@hehoe.de)
 * Created:   2018-03-31
 * Copyright: Hermann Höhne (www.hehoe.de)
 * License:   GNU GPLv3
 **************************************************************/

#include "hpicviewApp.hpp"

IMPLEMENT_APP(hpicviewApp);

bool hpicviewApp::OnInit() {
    /* from https://forums.wxwidgets.org/viewtopic.php?t=21065 */
    wxInitAllImageHandlers();

    this->frame = new hpicviewFrame(0L);

    this->frame->SetConfiguration();

    this->frame->Show();

    if (this->argc == 2) {
        this->frame->OpenFile(this->argv[1]);
    }

    Bind(wxEVT_CHAR_HOOK, &hpicviewApp::OnCharHook, this);

    return true;
}

int hpicviewApp::OnExit() {
    Unbind(wxEVT_CHAR_HOOK, &hpicviewApp::OnCharHook, this);
    return 0;
}

//#include <iostream>

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
            case WXK_SPACE:
            case WXK_RIGHT:
                this->frame->OnNext(ce);
            break;
            case '+':
            case WXK_ADD:
            case WXK_NUMPAD_ADD:
                this->frame->OnZoomIn(ce);
            break;
            case '-':
            case WXK_SUBTRACT:
            case WXK_NUMPAD_SUBTRACT:
                this->frame->OnZoomOut(ce);
            break;
            case WXK_ESCAPE:
                this->frame->OnEscape(ce);
            break;
            case WXK_RETURN:
                this->frame->OnToggleFullScreen(ce);
            break;
            default:
                //std::cerr << "Unbound key:" << event.GetKeyCode() << " / " << event.GetUnicodeKey() << std::endl;
                event.Skip();
            break;
        }
    }
}

