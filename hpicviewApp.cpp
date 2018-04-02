/***************************************************************
 * Name:      hpicviewApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Hermann Höhne (hermann@hehoe.de)
 * Created:   2018-03-31
 * Copyright: Hermann Höhne (www.hehoe.de)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "hpicviewApp.h"
#include "hpicviewMain.h"

IMPLEMENT_APP(hpicviewApp);

bool hpicviewApp::OnInit()
{
    /* from https://forums.wxwidgets.org/viewtopic.php?t=21065 */
    wxInitAllImageHandlers();

    hpicviewFrame* frame = new hpicviewFrame(0L);

    frame->Show();

    //frame->OpenFile(_("test_imperfect.jpg"));

    return true;
}
