///////////////////////////////////////////////////////////////////////////////
// Name:        src/generic/statbmpg.cpp
// Purpose:     wxSelectableStaticBitmap
// Author:      Hermann Höhne
// Created:     2021-06-29
// Copyright:   wxWidgets developers
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

/*
 * https://github.com/wxWidgets/wxWidgets/blob/master/src/generic/statbmpg.cpp
 * https://stackoverflow.com/questions/37937933/select-an-area-from-an-image-using-a-draggable-rectangle-using-wxwidget-in-c
 * 
 */

#include "wx/wxprec.h"

#if wxUSE_STATBMP

#ifndef WX_PRECOMP
    #include "wx/dcclient.h"
#endif

#include "sstatbmp.h"

#if wxUSE_GRAPHICS_CONTEXT
    #include "wx/graphics.h"
    #include "wx/scopedptr.h"
#else
    #error "wxSelectableStaticBitmap wants wxUSE_GRAPHICS_CONTEXT."
#endif

bool wxSelectableStaticBitmap::Create(wxWindow *parent, wxWindowID id,
                                   const wxBitmap& bitmap,
                                   const wxPoint& pos, const wxSize& size,
                                   long style, const wxString& name)
{
    if (! wxControl::Create(parent, id, pos, size, style,
                            wxDefaultValidator, name))
        return false;
    SetBitmap(bitmap);
    Bind(wxEVT_PAINT, &wxSelectableStaticBitmap::OnPaint, this);
    return true;
}

void wxSelectableStaticBitmap::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    if ( !m_bitmap.IsOk() ) {
        return;
    }
    wxPaintDC dc(this);
    const wxSize bmpSize = m_bitmap.GetSize();
    wxScopedPtr<wxGraphicsContext> const gc(wxGraphicsRenderer::GetDefaultRenderer()->CreateContext(dc));
    gc->DrawBitmap(m_bitmap, 0, 0, bmpSize.x, bmpSize.y);
    
    if (m_SelectionRectPtr) {
        wxRect * r = m_SelectionRectPtr.get();
        gc->SetPen(*wxBLACK_PEN); // TODO: use conplementary color
        gc->SetBrush(*wxTRANSPARENT_BRUSH);
        gc->DrawRectangle(r->x, r->y, r->width, r->height);
    }
}

// TODO: find out if this is doable without a define
#define adjust(x, width)     if (relativePosition.x > halfSize.x) { \
        selectionRect->width = relativePosition.x; \
    } else { \
        selectionRect->x = absolutePosition.x; \
        selectionRect->width = selectionRect->width - relativePosition.x; \
    }

void wxSelectableStaticBitmap::UpdateSelection(wxPoint absolutePosition) {
    if (!m_SelectionRectPtr) {
        wxScopedPtr<wxRect> srp(new wxRect(absolutePosition, wxSize(0, 0)));
        m_SelectionRectPtr.swap(srp);
    }
    wxRect * selectionRect = m_SelectionRectPtr.get();
    wxPoint relativePosition = absolutePosition - selectionRect->GetTopLeft();
    wxSize halfSize = selectionRect->GetSize()/2;
    adjust(x, width);
    adjust(y, height);
    // TODO: allow adjusting an edge instead of a corner
    Refresh();
}

void wxSelectableStaticBitmap::ClearSelection() {
    wxScopedPtr<wxRect> srp(nullptr);
    m_SelectionRectPtr.swap(srp);
    Refresh();
}

bool wxSelectableStaticBitmap::HasSelection() {
    return m_SelectionRectPtr;
}

const wxRect wxSelectableStaticBitmap::GetSelection() {
    wxASSERT(m_SelectionRectPtr);
    return *m_SelectionRectPtr;
}

// under OSX_cocoa is a define, avoid duplicate info
#ifndef wxSelectableStaticBitmap

wxIMPLEMENT_DYNAMIC_CLASS(wxSelectableStaticBitmap, wxStaticBitmapBase);

#endif

#endif // wxUSE_STATBMP
