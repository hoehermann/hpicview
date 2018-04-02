#ifndef REDO_SVG_PNG_H
#define REDO_SVG_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char redo_svg_png[] = 
{
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 
	0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x30, 
	0x00, 0x00, 0x00, 0x30, 0x08, 0x06, 0x00, 0x00, 0x00, 0x57, 
	0x02, 0xF9, 0x87, 0x00, 0x00, 0x00, 0x04, 0x73, 0x42, 0x49, 
	0x54, 0x08, 0x08, 0x08, 0x08, 0x7C, 0x08, 0x64, 0x88, 0x00, 
	0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x01, 
	0x4C, 0x00, 0x00, 0x01, 0x4C, 0x01, 0x69, 0x86, 0xBD, 0x39, 
	0x00, 0x00, 0x00, 0x19, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6F, 
	0x66, 0x74, 0x77, 0x61, 0x72, 0x65, 0x00, 0x77, 0x77, 0x77, 
	0x2E, 0x69, 0x6E, 0x6B, 0x73, 0x63, 0x61, 0x70, 0x65, 0x2E, 
	0x6F, 0x72, 0x67, 0x9B, 0xEE, 0x3C, 0x1A, 0x00, 0x00, 0x03, 
	0x4A, 0x49, 0x44, 0x41, 0x54, 0x68, 0x81, 0xCD, 0xDA, 0x4D, 
	0x68, 0x9C, 0x45, 0x1C, 0xC7, 0xF1, 0xCF, 0x6E, 0x8D, 0xD2, 
	0xC6, 0x04, 0xAB, 0x50, 0x69, 0x51, 0xA8, 0x88, 0x78, 0x51, 
	0x6A, 0x6C, 0x28, 0x15, 0x2F, 0x62, 0xA9, 0x88, 0x56, 0x09, 
	0x96, 0x5E, 0xF4, 0xA2, 0x27, 0x0F, 0x82, 0x50, 0xF1, 0x60, 
	0xE9, 0xCD, 0x17, 0x04, 0x2F, 0xA2, 0xAD, 0x82, 0x22, 0xA6, 
	0x77, 0x8F, 0x2D, 0xBE, 0x14, 0x05, 0x0F, 0x7A, 0x11, 0xEC, 
	0x25, 0x56, 0x5B, 0x91, 0x46, 0x11, 0x41, 0x10, 0xC4, 0x6E, 
	0xD2, 0xDA, 0x62, 0xD7, 0x78, 0x98, 0x5D, 0x9B, 0x6E, 0xF3, 
	0xCC, 0x33, 0xFB, 0x3C, 0xF3, 0x6C, 0xF2, 0x85, 0x21, 0x64, 
	0x9F, 0xC9, 0x7F, 0x7E, 0xBF, 0x79, 0xE6, 0xE5, 0xBF, 0x33, 
	0x69, 0xC9, 0x4F, 0x0B, 0x5B, 0x70, 0x13, 0xC6, 0xB1, 0x84, 
	0x05, 0x9C, 0xC5, 0x6F, 0xBD, 0xDF, 0x87, 0xE5, 0x39, 0xBC, 
	0x89, 0xB1, 0x81, 0xCF, 0x8F, 0x55, 0x97, 0x79, 0x99, 0x71, 
	0xCC, 0xE0, 0x6D, 0x9C, 0xC0, 0x39, 0x41, 0xE4, 0x4A, 0x65, 
	0x01, 0xDF, 0xF4, 0xEA, 0x3E, 0x82, 0x0D, 0x89, 0x6D, 0x7C, 
	0x14, 0x89, 0x59, 0x99, 0x69, 0xCC, 0xA2, 0x13, 0x09, 0x5E, 
	0x56, 0x16, 0xF1, 0x3E, 0xEE, 0x2D, 0x69, 0x6B, 0x36, 0xA7, 
	0x81, 0xED, 0xF8, 0xAC, 0x86, 0xE8, 0xA2, 0x72, 0x0C, 0x77, 
	0x17, 0xB4, 0x79, 0x28, 0x87, 0x81, 0x09, 0x1C, 0xC6, 0xA5, 
	0x06, 0xC4, 0xF7, 0x4B, 0x57, 0x18, 0xEB, 0xEB, 0x07, 0xDA, 
	0x7E, 0xBD, 0xAE, 0x81, 0x6D, 0x38, 0xDD, 0xA0, 0xF0, 0xC1, 
	0xF2, 0x83, 0x2B, 0xDF, 0xC6, 0xC1, 0x3A, 0x06, 0xF6, 0x88, 
	0x4F, 0xCC, 0xA6, 0x4A, 0x07, 0x0F, 0xF7, 0x34, 0x3C, 0x5F, 
	0x54, 0xEF, 0x9A, 0x12, 0xF1, 0x4F, 0xE1, 0x08, 0xCA, 0xEA, 
	0x2D, 0xE7, 0x17, 0xCC, 0x61, 0x1E, 0xE7, 0x7B, 0x9F, 0xDD, 
	0x80, 0x5B, 0x31, 0x85, 0xCD, 0x89, 0x71, 0x26, 0x70, 0x14, 
	0x4F, 0x0A, 0x93, 0x7D, 0x68, 0x1E, 0xC3, 0x3F, 0xD2, 0x7A, 
	0x6B, 0x0E, 0xFB, 0xB1, 0x35, 0x21, 0xEE, 0x1D, 0x78, 0x09, 
	0x3F, 0x26, 0xC6, 0xBE, 0x28, 0x74, 0xE2, 0x50, 0x43, 0x68, 
	0x9B, 0xD0, 0x7B, 0x65, 0xC1, 0xBF, 0x17, 0x86, 0x58, 0x2B, 
	0x41, 0xF8, 0x20, 0x6D, 0xEC, 0xC3, 0x4F, 0x89, 0x46, 0x92, 
	0x0D, 0x4C, 0x28, 0x9F, 0xB0, 0x5D, 0xBC, 0xEC, 0xEA, 0x9D, 
	0xB1, 0x0A, 0xEB, 0xF1, 0x06, 0xFE, 0xCD, 0x65, 0xE0, 0x70, 
	0xC9, 0x1F, 0x2C, 0xB8, 0x3C, 0xB9, 0x72, 0xB2, 0x57, 0xB5, 
	0xC5, 0xE2, 0x0A, 0xB6, 0x8B, 0xAF, 0xF3, 0x0B, 0xD8, 0xD9, 
	0x80, 0xF8, 0x3E, 0xBB, 0xA4, 0x0D, 0xDD, 0x42, 0x03, 0xB1, 
	0x1D, 0xB6, 0xAB, 0x99, 0x9E, 0x1F, 0x64, 0xAF, 0x21, 0x86, 
	0xD3, 0xF2, 0xE5, 0x71, 0x1A, 0x0F, 0x45, 0x02, 0xBF, 0x8A, 
	0x4F, 0x6B, 0x8A, 0x7B, 0x16, 0x0F, 0x08, 0x6B, 0x7C, 0x47, 
	0xE8, 0xED, 0x73, 0xF8, 0xAB, 0xF7, 0xF3, 0xBC, 0x90, 0xB5, 
	0x7E, 0x22, 0x24, 0x7B, 0x43, 0x31, 0xAB, 0xD8, 0xE9, 0x49, 
	0xF5, 0x27, 0x6C, 0x5B, 0xFA, 0xB2, 0x3C, 0xF4, 0x10, 0x1A, 
	0x17, 0xCF, 0x2A, 0xF7, 0xD4, 0x14, 0x4F, 0xD8, 0x0C, 0x73, 
	0x8B, 0xFF, 0xDF, 0xC0, 0x4C, 0xA4, 0xC2, 0x9C, 0x6A, 0xEB, 
	0xFC, 0x48, 0x0C, 0xB4, 0x7B, 0xC1, 0x1F, 0x8C, 0x34, 0xFC, 
	0xA1, 0x15, 0x66, 0xFB, 0x5A, 0xE3, 0x5B, 0xC5, 0x2E, 0xB7, 
	0x66, 0x6A, 0xA3, 0xB1, 0x21, 0xD4, 0x12, 0x92, 0xA5, 0x95, 
	0x1E, 0xFE, 0x9C, 0x49, 0x7C, 0x9F, 0x2F, 0x33, 0x8B, 0x3F, 
	0x0E, 0xB7, 0x44, 0x2A, 0x1C, 0xCD, 0x6C, 0x20, 0x3B, 0x6D, 
	0x6C, 0x8C, 0x3C, 0x9F, 0x1F, 0x95, 0x90, 0xAA, 0xB4, 0x85, 
	0xE4, 0xAD, 0x88, 0xCE, 0xA8, 0x84, 0x54, 0xA5, 0x5D, 0x5E, 
	0x65, 0x6D, 0xD3, 0x16, 0x12, 0xB4, 0x22, 0x26, 0x47, 0x25, 
	0xA4, 0x2A, 0x6D, 0xFC, 0x19, 0x79, 0x7E, 0xDB, 0xA8, 0x84, 
	0xD4, 0x61, 0x94, 0xCB, 0x68, 0x63, 0x9C, 0x50, 0xBC, 0x94, 
	0xAE, 0xE9, 0xB7, 0xD0, 0x9F, 0xC4, 0x5F, 0x45, 0xEA, 0x3C, 
	0x31, 0x0A, 0x21, 0x75, 0x89, 0x25, 0x73, 0xDF, 0xC9, 0x93, 
	0xCC, 0x35, 0xCA, 0xB8, 0xB0, 0x1A, 0x15, 0x99, 0x78, 0x7C, 
	0xF5, 0xA4, 0xA5, 0x73, 0x44, 0xB1, 0x81, 0xD3, 0xB8, 0x6E, 
	0xD5, 0x94, 0x25, 0xB2, 0x43, 0x3C, 0x71, 0x7A, 0x65, 0xF5, 
	0xA4, 0xA5, 0x73, 0x5C, 0xB1, 0x81, 0xAE, 0x0A, 0xDF, 0x53, 
	0x47, 0xCD, 0xB4, 0x20, 0xB4, 0xC8, 0xC4, 0x22, 0xEE, 0x5B, 
	0x35, 0x75, 0x89, 0xBC, 0x2B, 0x3E, 0x94, 0x16, 0x35, 0xF3, 
	0x26, 0xF6, 0x09, 0x87, 0x07, 0xFB, 0xEB, 0x06, 0x9A, 0x54, 
	0x7E, 0xF0, 0xDA, 0xC5, 0x6B, 0xB8, 0xB6, 0x6E, 0x63, 0xC2, 
	0xD1, 0xE2, 0x7B, 0x03, 0xF1, 0x0F, 0xD4, 0x0D, 0x3A, 0x85, 
	0xBF, 0xC5, 0x4D, 0x2C, 0xE1, 0x94, 0xB0, 0x87, 0x54, 0xD9, 
	0x27, 0xC6, 0xF0, 0x8C, 0xE2, 0xC3, 0xDD, 0xDA, 0x26, 0x66, 
	0xA4, 0x5F, 0x27, 0x9D, 0xC4, 0x8B, 0xB8, 0xBD, 0x24, 0x66, 
	0x4B, 0x38, 0xBE, 0x3C, 0x88, 0x33, 0x09, 0x71, 0x5F, 0x28, 
	0x13, 0x59, 0xD6, 0x73, 0x4F, 0xE3, 0x03, 0xAC, 0x2B, 0x0B, 
	0xB4, 0x8C, 0x5F, 0x85, 0xDD, 0x7B, 0x5E, 0xD8, 0x1C, 0xC7, 
	0xB0, 0x49, 0xB8, 0xD8, 0xB8, 0x0B, 0x37, 0x0F, 0x11, 0xEB, 
	0x8C, 0xF2, 0x4E, 0x29, 0x65, 0x46, 0xDA, 0x70, 0xCA, 0x5D, 
	0x3A, 0x78, 0xB4, 0xAE, 0xF8, 0x3E, 0x53, 0xD2, 0x6F, 0x54, 
	0x72, 0x94, 0x53, 0xC2, 0xDB, 0xCA, 0xCA, 0x24, 0xDE, 0x11, 
	0xDF, 0x27, 0xEA, 0x96, 0x4B, 0x78, 0xCB, 0xD5, 0xD7, 0xAC, 
	0x59, 0x99, 0xD6, 0xCC, 0x45, 0xF7, 0xC7, 0x8A, 0x2F, 0xBA, 
	0x1B, 0x61, 0x87, 0x90, 0x00, 0xD6, 0xF9, 0x57, 0x83, 0xB3, 
	0xC2, 0xA9, 0xF8, 0x3D, 0x55, 0x45, 0xE4, 0xC8, 0xF3, 0x37, 
	0x60, 0xB7, 0x70, 0xBE, 0x7A, 0x3F, 0xEE, 0xC4, 0xF5, 0x05, 
	0x75, 0x17, 0x85, 0x4B, 0xEC, 0xAF, 0xF1, 0x05, 0x3E, 0xC7, 
	0x85, 0x3A, 0x8D, 0x37, 0xF5, 0x45, 0x65, 0x0B, 0x6E, 0x14, 
	0xCE, 0x9C, 0x96, 0x84, 0xCB, 0x8B, 0x3F, 0xF0, 0x7B, 0xEE, 
	0x86, 0xFE, 0x03, 0xFD, 0x75, 0xF1, 0xFC, 0x61, 0xE3, 0x69, 
	0x5A, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 
	0x42, 0x60, 0x82, 
};

wxBitmap& redo_svg_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( redo_svg_png, sizeof( redo_svg_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_PNG );
	static wxBitmap bmp( image );
	return bmp;
};


#endif //REDO_SVG_PNG_H
