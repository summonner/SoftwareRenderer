#pragma once
#include <windows.h>
#include <gl/gl.h>
struct AUX_RGBImageRec final
{
	GLsizei sizeX, sizeY;
	BYTE* data;
};

AUX_RGBImageRec* auxDIBImageLoad( LPCTSTR filename );