#pragma once

#include <set>
#include <wx/string.h>

std::set<wxString> GetImageExts(bool include_alternatives = true);
wxString GetImageExtWildcard(std::set<wxString> image_extensions);
