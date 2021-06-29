///////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/sstatbmp.h
// Purpose:     wxSelectableStaticBitmap header
// Author:      Hermann Höhne
// Created:     2021-06-29
// Copyright:   wxWidgets developers
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

/*
 * https://github.com/wxWidgets/wxWidgets/blob/master/include/wx/generic/statbmpg.h
 */
 
#ifndef _WX_SSTATBMP_H_
#define _WX_SSTATBMP_H_

#include "wx/statbmp.h"

class WXDLLIMPEXP_CORE wxSelectableStaticBitmap : public wxStaticBitmapBase
{
public:
    wxSelectableStaticBitmap() {}
    wxSelectableStaticBitmap(wxWindow *parent,
                          wxWindowID id,
                          const wxBitmap& bitmap,
                          const wxPoint& pos = wxDefaultPosition,
                          const wxSize& size = wxDefaultSize,
                          long style = 0,
                          const wxString& name = wxStaticBitmapNameStr)
    {
            Create(parent, id, bitmap, pos, size, style, name);
    }

    bool Create(wxWindow *parent,
                wxWindowID id,
                const wxBitmap& bitmap,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxString& name = wxStaticBitmapNameStr);

    virtual void SetBitmap(const wxBitmap& bitmap) wxOVERRIDE
    {
        m_bitmap = bitmap;
        SetInitialSize(GetBitmapSize());
        Refresh();
    }

    virtual wxBitmap GetBitmap() const wxOVERRIDE { return m_bitmap; }
    
    virtual void SetIcon(const wxIcon& icon) wxOVERRIDE
    {
        m_bitmap.CopyFromIcon(icon);
        SetInitialSize(GetBitmapSize());
        Refresh();
    }

#if defined(__WXGTK20__) || defined(__WXMAC__)
    // icons and bitmaps are really the same thing in wxGTK and wxMac
    wxIcon GetIcon() const wxOVERRIDE  { return (const wxIcon &)m_bitmap; }
#endif
    
    virtual void UpdateSelection(wxPoint absolutePosition);
    virtual void ClearSelection();
    virtual const wxRect GetSelection();
    virtual bool HasSelection();

private:
    wxSize GetBitmapSize()
    {
        return m_bitmap.IsOk() ? m_bitmap.GetScaledSize()
                               : wxSize(16, 16); // this is completely arbitrary
    }
    
    void OnPaint(wxPaintEvent& event);

    wxBitmap m_bitmap;
    
    wxScopedPtr<wxRect> m_SelectionRectPtr;

    wxDECLARE_DYNAMIC_CLASS(wxSelectableStaticBitmap);
};


#endif //_WX_SSTATBMP_H_
