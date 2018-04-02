/***************************************************************
 * Name:      hpicviewMain.h
 * Purpose:   Defines Application Frame
 * Author:    Hermann Höhne (hermann@hehoe.de)
 * Created:   2018-03-31
 * Copyright: Hermann Höhne (www.hehoe.de)
 * License:
 **************************************************************/

#ifndef HPICVIEWMAIN_H
#define HPICVIEWMAIN_H

#include "hpicviewApp.h"
#include "GUIFrame.h"
#include "jpegtran.h"
#include <string>

class hpicviewFrame: public GUIFrame
{
    public:
        hpicviewFrame(wxFrame *frame);
        ~hpicviewFrame();
        void OpenFile(wxString filename);
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OnFileOpen(wxCommandEvent& event);
		virtual void OnRotateRight(wxCommandEvent& event);
        JPEGtran jpegtran;
        std::string jpegdata;
        void SetJPEG(const std::string & jpegdata);
        static std::string get_file_contents(wxString filename);
};

#endif // HPICVIEWMAIN_H
