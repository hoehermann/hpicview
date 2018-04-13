/***************************************************************
 * Name:      hpicviewApp.h
 * Purpose:   Defines Application Class
 * Author:    Hermann Höhne (hermann@hehoe.de)
 * Created:   2018-03-31
 * Copyright: Hermann Höhne (www.hehoe.de)
 * License:
 **************************************************************/

#ifndef HPICVIEWAPP_H
#define HPICVIEWAPP_H

#include <wx/app.h>

class hpicviewFrame;

class hpicviewApp : public wxApp
{
    public:
        virtual bool OnInit();
        virtual int OnExit();
    private:
        virtual void OnCharHook(wxKeyEvent& event);
        hpicviewFrame* frame;
};

#endif // HPICVIEWAPP_H
