#include "framework.h"
#include "Bitmap.h"
#include "Math/Vector2.hpp"

Bitmap::Bitmap( BITMAPINFOHEADER info, BYTE* data, RGBQUAD* palette )
	: IImageSource( info.biWidth, info.biHeight )
	, rowSize( info.biSizeImage / info.biHeight )
	, pixels( data )
	, pixelSize( info.biBitCount / 8 )
	, palette( palette )
{
}

Bitmap::~Bitmap()
{
}

std::shared_ptr<Bitmap> Bitmap::Load( LPCTSTR filePath )
{
	FILE* file;
	auto err = _tfopen_s( &file, filePath, _T( "rb" ) );
	if ( err != 0 )
	{
		return nullptr;
	}

	auto bitmap = Parse( file );
	fclose( file );
	return bitmap;
}

std::shared_ptr<Bitmap> Bitmap::Parse( FILE* file )
{
	BITMAPFILEHEADER header;
	if ( fread( &header, sizeof( BITMAPFILEHEADER ), 1, file ) != 1 )
	{
		return nullptr;
	}

	if ( header.bfType != BM )
	{
		return nullptr;
	}

	BITMAPINFOHEADER info;
	if ( fread( &info, sizeof( BITMAPINFOHEADER ), 1, file ) != 1 )
	{
		return nullptr;
	}

	if ( info.biSizeImage == 0 )
	{
		auto rowSize = (info.biWidth + 3) & ~3;
		info.biSizeImage = rowSize * info.biHeight * (info.biBitCount / 8);
	}

	auto palette = ParsePalette( file, info );
	auto data = new BYTE[info.biSizeImage];
	fread( data, sizeof( BYTE ), info.biSizeImage, file );

	return std::shared_ptr<Bitmap>( new Bitmap( info, data, palette ) );
}

RGBQUAD* Bitmap::ParsePalette( FILE* file, BITMAPINFOHEADER& info )
{
	if ( info.biCompression != BI_RGB || info.biBitCount > 8 )
	{
		return nullptr;
	}

	if ( info.biClrUsed == 0 )
	{
		info.biClrUsed = 1 << info.biBitCount;
	}

	auto palette = new RGBQUAD[info.biClrUsed];
	fread( palette, sizeof( RGBQUAD ), info.biClrUsed, file );
	return palette;
}

Color4 Bitmap::GetPixel( const Vector2Int& p ) const
{
	auto i = p.x * pixelSize + p.y * rowSize;
	switch ( pixelSize )
	{
	case 3:
		return Color4( pixels[i + 2],
					   pixels[i + 1],
					   pixels[i + 0],
					   255 );
	case 1:
		if ( palette == nullptr )
		{
			assert( "Unknown format" && false );
			return Color4::zero;
		}
		auto color = palette[pixels[i]];
		return Color4( color.rgbRed,
					   color.rgbGreen,
					   color.rgbBlue, 
					   255 );

	default:
		assert( "Not implemented yet" && false );
		return Color4::zero;
	}
}

Vector4 Bitmap::GetPixel( const Vector2& p ) const
{
	Vector2Int coord( width - 1, height - 1 );
	coord.x = (int)(coord.x * p.x);
	coord.y = (int)(coord.y * p.y);
	
	auto color = GetPixel( coord );
	return Vector4( color.x / 255.f,
					color.y / 255.f,
					color.z / 255.f,
					color.w / 255.f );
}