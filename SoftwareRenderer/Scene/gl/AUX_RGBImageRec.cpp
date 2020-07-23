#include "framework.h"
#include "AUX_RGBImageRec.h"
#include "Util/Bitmap.h"

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
		data[i + 0] = color.x;
		data[i + 1] = color.y;
		data[i + 2] = color.z;
	}

	auto image = new AUX_RGBImageRec();
	image->data = data;
	image->sizeX = bitmap->width;
	image->sizeY = bitmap->height;
	return image;
}