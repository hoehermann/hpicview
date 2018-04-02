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

#include <boost/filesystem.hpp>

class hpicviewFrame: public GUIFrame
{
    public:
        hpicviewFrame(wxFrame *frame);
        ~hpicviewFrame();
        void OpenFile(const wxString & filename); // only public for debugging reasons
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OnFileOpen(wxCommandEvent& event);
        virtual void OnRotateLeft(wxCommandEvent& event);
		virtual void OnRotateRight(wxCommandEvent& event);

        void SetJPEG(const std::string & jpegdata);
        void WriteIfDirty();
        void Write(const wxString & filename);

        // these represent the currently loaded image
        wxString filename;
        std::time_t modification_date;
        std::string jpegdata;
        bool dirty;
};

#endif // HPICVIEWMAIN_H
