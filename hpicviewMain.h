/***************************************************************
 * Name:      hpicviewMain.h
 * Purpose:   Defines Application Frame
 * Author:    Hermann Höhne (hermann@hehoe.de)
 * Created:   2018-03-31
 * Copyright: Hermann Höhne (www.hehoe.de)
 * License:
 **************************************************************/

#pragma once

#include "GUIFrame.h"
#include "jpegtran.h"
#include <string>

#include <boost/filesystem.hpp>
#include <set>

class hpicviewFrame: public GUIFrame
{
    public:
        hpicviewFrame(wxFrame *frame);
        ~hpicviewFrame();
        void OpenFile(const wxString & filename);
        // TODO: introduce separate methods not being handlers?
        virtual void OnPrevious(wxCommandEvent& event);
        virtual void OnNext(wxCommandEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnRotateLeft(wxCommandEvent& event);
        virtual void OnRotateRight(wxCommandEvent& event);
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OnOpen(wxCommandEvent& event);

        void SetImageData(const std::string & imagedata);
        void WriteIfDirty();
        void Write(const wxString & filename); // TODO: switch to boost::filesystem::path
        void SetPosition(const std::vector<boost::filesystem::path>::iterator & p);
        std::vector<boost::filesystem::path>::iterator UpdateDirectoryListing(const boost::filesystem::path & path);

        // these represent the currently loaded image
        boost::filesystem::path filename;
        std::time_t modification_date;
        std::string imagedata;
        wxImage m_image;
        bool dirty;

        // for walking the directory
        std::vector<boost::filesystem::path> filenames_images;
        std::vector<boost::filesystem::path>::iterator filenames_position;

        // configuration
        std::set<wxString> image_extensions;
};
