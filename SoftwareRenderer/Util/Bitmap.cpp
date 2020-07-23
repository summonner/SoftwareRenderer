#include "framework.h"
#include "Bitmap.h"
#include "Math/Vector2.hpp"

Bitmap::Bitmap( BITMAPINFOHEADER info, BYTE* data )
	: IImageSource( info.biWidth, info.biHeight )
	, rowSize( info.biSizeImage / info.biHeight )
	, pixels( data )
	, pixelSize( info.biBitCount / 8 )
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

	BITMAPINFOHEADER info;
	auto bytes = Parse( file, info );
	fclose( file );
	if ( bytes == nullptr )
	{
		return nullptr;
	}

	return std::shared_ptr<Bitmap>( new Bitmap( info, bytes ) );
}

BYTE* Bitmap::Parse( FILE* file, BITMAPINFOHEADER& outInfo )
{
	BITMAPFILEHEADER header;
	if ( fread( &header, sizeof( BITMAPFILEHEADER ), 1, file ) != 1 )
	{
		return nullptr;
	}

	if ( header.bfType != 0x4D42 )
	{
		return nullptr;
	}

	if ( fread( &outInfo, sizeof( BITMAPINFOHEADER ), 1, file ) != 1 )
	{
		return nullptr;
	}

	if ( outInfo.biSizeImage == 0 )
	{
		auto rowSize = (outInfo.biWidth + 3) & ~3;
		outInfo.biSizeImage = rowSize * outInfo.biHeight * (outInfo.biBitCount / 8);
	}

	auto bytes = new BYTE[outInfo.biSizeImage];
	fread( bytes, sizeof( BYTE ), outInfo.biSizeImage, file );
	return bytes;
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