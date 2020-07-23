#include <memory>
#include <tchar.h>
#include "AUX_RGBImageRec.h"
#include "Bitmap.h"

AUX_RGBImageRec* auxDIBImageLoad( LPCTSTR filePath )
{
	auto bitmap = Bitmap::Load( filePath );
	if ( bitmap == nullptr )
	{
		return nullptr;
	}

	auto data = new BYTE[bitmap->width * bitmap->height * 3];
	for ( auto p : *bitmap )
	{
		auto color = bitmap->GetPixel( p );
		auto i = (p.y * bitmap->width + p.x) * 3;
		data[i + 0] = (int)(color.x * 255);
		data[i + 1] = (int)(color.y * 255);
		data[i + 2] = (int)(color.z * 255);
	}

	auto image = new AUX_RGBImageRec();
	image->data = data;
	image->sizeX = bitmap->width;
	image->sizeY = bitmap->height;
	return image;
}