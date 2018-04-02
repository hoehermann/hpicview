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

class hpicviewApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // HPICVIEWAPP_H
