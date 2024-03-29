/***************************************************************
 * Name:      hpicviewMain.h
 * Purpose:   Defines Application Frame
 * Author:    Hermann Höhne (hermann@hehoe.de)
 * Created:   2018-03-31
 * Copyright: Hermann Höhne (www.hehoe.de)
 * License:   GNU GPLv3
 **************************************************************/

#pragma once

#include "GUIFrame.h"
#include "jpegtran.hpp"
#include <string>

#include <filesystem>
#include <vector>
#include <set>

wxString std_string_to_wxString(const std::string & stdstring);

class hpicviewFrame: public GUIFrame
{
    public:
        hpicviewFrame(wxFrame *frame);
        ~hpicviewFrame();
        void OpenPath(const wxString & pathname);
        // TODO: introduce separate methods not being handlers?
        virtual void OnPrevious(wxCommandEvent& event);
        virtual void OnNext(wxCommandEvent& event);
        virtual void OnDelete(wxCommandEvent& event);
        virtual void OnRotateLeft(wxCommandEvent& event);
        virtual void OnRotateRight(wxCommandEvent& event);
        virtual void OnZoomOut(wxCommandEvent& event);
        virtual void OnZoomIn(wxCommandEvent& event);
        virtual void OnToggleFullScreen(wxCommandEvent& event);
        virtual void OnEscape(wxCommandEvent& event);
        virtual void LoadConfiguration();
        void CopyToClipboard();
    private:
        void OpenFile(const wxString & filename);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnSize(wxSizeEvent& event);
        virtual void ZoomFit();
        virtual void FitAndDisplay();
        virtual void OnZoomFit(wxCommandEvent& event);
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OnOpen(wxCommandEvent& event);
        virtual void OnLeftDown(wxMouseEvent& event);
        virtual void OnRightUp(wxMouseEvent& event);
        virtual void OnMotion(wxMouseEvent& event);
        bool OnDropFile(wxCoord, wxCoord, const wxArrayString& paths);

        void SetImageData(const std::string & imagedata);
        void WriteIfDirty();
        void Write(const wxString & filename); // TODO: switch to filesystem::path
        void ScaleImage(float view_zoom_exponent, wxImageResizeQuality quality);
        void SetViewZoomExponent(float view_zoom_exponent);

        // these represent the currently loaded image
        std::filesystem::path m_filename;
        std::filesystem::file_time_type m_modification_date;
        std::string m_imagedata;
        wxImage m_image;
        bool m_dirty;

        // for walking the directory
        std::vector<std::filesystem::path>::iterator UpdateDirectoryListing(std::filesystem::path path);
        void SetFileIndex(const std::vector<std::filesystem::path>::iterator & p);
        std::vector<std::filesystem::path> filenames_images;
        std::vector<std::filesystem::path>::iterator filenames_position;

        // configuration
        std::set<wxString> m_image_extensions;

        // view
        int m_view_zoom_exponent = 0;

        enum statusbar_columns {
            STATUSBAR_COLUMN_MAIN = 0,
            STATUSBAR_COLUMN_ZOOM = 1,
            STATUSBAR_COLUMN_INDEX = 2
        };
};
