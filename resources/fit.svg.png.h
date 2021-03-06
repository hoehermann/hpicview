#ifndef FIT_SVG_PNG_H
#define FIT_SVG_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char fit_svg_png[] =
{
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 
	0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x30, 
	0x00, 0x00, 0x00, 0x30, 0x08, 0x06, 0x00, 0x00, 0x00, 0x57, 
	0x02, 0xF9, 0x87, 0x00, 0x00, 0x00, 0x04, 0x73, 0x42, 0x49, 
	0x54, 0x08, 0x08, 0x08, 0x08, 0x7C, 0x08, 0x64, 0x88, 0x00, 
	0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x01, 
	0x62, 0x00, 0x00, 0x01, 0x62, 0x01, 0x5F, 0x27, 0xD0, 0x53, 
	0x00, 0x00, 0x00, 0x19, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6F, 
	0x66, 0x74, 0x77, 0x61, 0x72, 0x65, 0x00, 0x77, 0x77, 0x77, 
	0x2E, 0x69, 0x6E, 0x6B, 0x73, 0x63, 0x61, 0x70, 0x65, 0x2E, 
	0x6F, 0x72, 0x67, 0x9B, 0xEE, 0x3C, 0x1A, 0x00, 0x00, 0x02, 
	0x13, 0x49, 0x44, 0x41, 0x54, 0x68, 0x81, 0xED, 0xD9, 0xBF, 
	0x6A, 0x14, 0x41, 0x00, 0xC7, 0xF1, 0x4F, 0x2E, 0x11, 0x8C, 
	0x17, 0x7D, 0x03, 0xAB, 0x34, 0x76, 0x11, 0x04, 0x21, 0x22, 
	0xD8, 0x89, 0x22, 0x62, 0x69, 0x61, 0x27, 0xD8, 0xFB, 0x02, 
	0x62, 0xF4, 0x09, 0xEC, 0x05, 0xBB, 0xBC, 0x80, 0x22, 0xFE, 
	0xE9, 0x02, 0xF1, 0xAC, 0x2C, 0x62, 0x63, 0x91, 0xE4, 0x25, 
	0x4C, 0x0E, 0x04, 0x2F, 0x17, 0x8B, 0xB9, 0x83, 0x45, 0x6F, 
	0x26, 0x3B, 0x77, 0x7B, 0xBB, 0x27, 0xEC, 0x17, 0xB6, 0xB8, 
	0x9D, 0x9D, 0xBD, 0xEF, 0x6F, 0xFF, 0xCC, 0xCC, 0xCE, 0xD0, 
	0xD2, 0x52, 0x09, 0x17, 0xF0, 0x12, 0x07, 0x18, 0xE0, 0x74, 
	0x41, 0xB7, 0xC1, 0xC8, 0xF1, 0x05, 0x56, 0x8B, 0xF2, 0x5F, 
	0x17, 0x40, 0x2E, 0x77, 0xEB, 0x61, 0x75, 0x19, 0xCF, 0xF0, 
	0x28, 0x7D, 0x83, 0x16, 0x92, 0xCB, 0x18, 0x2C, 0x09, 0xB7, 
	0x64, 0xBD, 0x61, 0x99, 0x69, 0x39, 0x58, 0x12, 0x9E, 0xAB, 
	0xE5, 0xC2, 0xCE, 0x1F, 0x78, 0xDB, 0x8C, 0xCF, 0x99, 0x3C, 
	0xC0, 0x95, 0xC2, 0xEF, 0x13, 0xFE, 0x7D, 0xB6, 0xB6, 0x6A, 
	0xD7, 0x2A, 0xCF, 0x96, 0xBF, 0x7C, 0x57, 0x12, 0x07, 0xBF, 
	0xC2, 0xCD, 0x48, 0xD9, 0x10, 0x4F, 0xB0, 0x57, 0x91, 0xD8, 
	0x06, 0x5E, 0xA3, 0x13, 0x29, 0xDF, 0xC5, 0xD3, 0x49, 0x05, 
	0xA9, 0x00, 0xB7, 0x70, 0x35, 0x52, 0xD6, 0xC3, 0x61, 0x59, 
	0xBB, 0x12, 0x1C, 0xE2, 0x37, 0x6E, 0x44, 0xCA, 0x97, 0x23, 
	0xFB, 0xA3, 0x89, 0x53, 0xF4, 0x70, 0x17, 0xC7, 0x53, 0xD4, 
	0x8D, 0x71, 0x8C, 0xDB, 0xD8, 0xC9, 0xAD, 0x98, 0x1B, 0x60, 
	0x2C, 0xFF, 0x33, 0xF7, 0x8F, 0x4A, 0xD0, 0xC7, 0x3D, 0x99, 
	0x21, 0x72, 0x02, 0xCC, 0x53, 0x7E, 0x4C, 0x76, 0x88, 0xB2, 
	0x01, 0xEA, 0x90, 0x1F, 0x93, 0x15, 0xA2, 0x4C, 0x80, 0x3A, 
	0xE5, 0xC7, 0x94, 0x0E, 0x91, 0x0A, 0x30, 0x14, 0xE4, 0xEF, 
	0xA8, 0x57, 0x7E, 0x4C, 0x1F, 0xF7, 0x47, 0x0E, 0xC3, 0xD8, 
	0x41, 0xA9, 0x66, 0xF4, 0xB1, 0x30, 0xCC, 0xE8, 0x57, 0xEB, 
	0x95, 0xC5, 0x91, 0xD0, 0x3A, 0x45, 0x87, 0x3A, 0xA9, 0x00, 
	0x55, 0x75, 0x52, 0xB3, 0xD2, 0xC7, 0xF7, 0x58, 0xE1, 0x34, 
	0xFD, 0xC0, 0x42, 0xD1, 0x06, 0x68, 0x9A, 0x36, 0x40, 0xD3, 
	0xB4, 0x01, 0x9A, 0xA6, 0x0D, 0xD0, 0x34, 0x6D, 0x80, 0xA6, 
	0x49, 0x05, 0xD8, 0x40, 0xB7, 0x2E, 0x91, 0x04, 0x5D, 0xC1, 
	0x65, 0x22, 0xA9, 0xC1, 0xDC, 0x1B, 0xFC, 0x12, 0x86, 0xD3, 
	0x47, 0x15, 0x4B, 0x95, 0xE5, 0x22, 0x3E, 0xE2, 0x3C, 0xAE, 
	0x4D, 0x3A, 0x20, 0x75, 0x07, 0x3A, 0xC2, 0x2C, 0xC1, 0x27, 
	0x5C, 0xAA, 0x5C, 0xED, 0x6C, 0xBA, 0x78, 0x37, 0x72, 0x88, 
	0x7A, 0x96, 0x79, 0x07, 0x36, 0x85, 0xAB, 0x50, 0x67, 0x88, 
	0x2E, 0xDE, 0x0B, 0x53, 0x3B, 0x49, 0xCA, 0xBE, 0xC4, 0x75, 
	0x86, 0x28, 0x2D, 0x4F, 0x5E, 0x2B, 0x54, 0x47, 0x88, 0x2C, 
	0x79, 0xF2, 0x9B, 0xD1, 0x79, 0x86, 0xC8, 0x96, 0x67, 0xBA, 
	0x7E, 0x60, 0x13, 0x1F, 0xB0, 0x36, 0x45, 0xDD, 0x18, 0x6B, 
	0xF8, 0x2C, 0x53, 0x9E, 0x74, 0x33, 0xBA, 0x63, 0x34, 0x7D, 
	0x3D, 0x81, 0x73, 0xC2, 0x87, 0x76, 0x55, 0xDF, 0xCD, 0xEB, 
	0xA3, 0x73, 0x7E, 0x8B, 0x94, 0xEF, 0xC6, 0x2A, 0xA6, 0x02, 
	0x4C, 0x9C, 0x0D, 0x9E, 0x13, 0x7B, 0xB8, 0x3E, 0x4D, 0xC5, 
	0x15, 0xE1, 0x2A, 0x17, 0x67, 0x7F, 0x1F, 0x0A, 0x1D, 0xD8, 
	0xE9, 0xEC, 0x5E, 0x95, 0xB2, 0x24, 0xB8, 0x15, 0x39, 0xF9, 
	0xDF, 0x97, 0x98, 0xF6, 0x3B, 0xD8, 0x6E, 0xDA, 0x62, 0x06, 
	0xB6, 0x09, 0xEB, 0xAD, 0x3D, 0xCD, 0x2F, 0x9B, 0xE6, 0x6E, 
	0x5F, 0x14, 0xD6, 0x8A, 0x57, 0x85, 0xF5, 0xA7, 0x7D, 0x8B, 
	0xBF, 0xD0, 0xBD, 0x8F, 0xE7, 0x45, 0xF9, 0x96, 0x96, 0x19, 
	0xF8, 0x03, 0xD9, 0xAE, 0x08, 0x87, 0x39, 0x1A, 0xB4, 0xD9, 
	0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 
	0x60, 0x82, 
};

wxBitmap& fit_svg_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( fit_svg_png, sizeof( fit_svg_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_PNG );
	static wxBitmap bmp( image );
	return bmp;
}


#endif //FIT_SVG_PNG_H
