#pragma once

#include <wx/dnd.h>

/* from https://forums.wxwidgets.org/viewtopic.php?t=35912 */
template <class T>
class FileDropTarget : public wxFileDropTarget {
public:
    typedef bool(T::*DropHandlerFunc)(wxCoord, wxCoord, const wxArrayString&);

    FileDropTarget(DropHandlerFunc function, T* handler) {
        wxASSERT(function);
        wxASSERT(handler);

        m_function = function;
        m_handler = handler;
    }

    virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString &fileNames) {
        return (m_handler->*m_function)(x, y, fileNames);
    }
private:
    DropHandlerFunc m_function;
    T* m_handler;
};
