/***************************************************************
 * Name:      hpicviewApp.h
 * Purpose:   Defines Application Class
 * Author:    Hermann Höhne (hermann@hehoe.de)
 * Created:   2018-03-31
 * Copyright: Hermann Höhne (www.hehoe.de)
 * License:
 **************************************************************/

#pragma once

#include <wx/app.h>

#include "hpicviewMain.hpp"

class hpicviewApp : public wxApp
{
    public:
        virtual bool OnInit();
        virtual int OnExit();
    private:
        virtual void OnCharHook(wxKeyEvent& event);
        hpicviewFrame* frame;
};
