#include "framework.h"
#include "Bitmap.h"
#include "Math/Vector2.hpp"

Bitmap::Bitmap( BITMAPINFOHEADER info, BYTE* data )
	: width( info.biWidth )
	, height( info.biHeight )
	, rowSize( info.biSizeImage / info.biHeight )
	, pixels( data )
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

	auto bytes = new BYTE[outInfo.biSizeImage];
	fread( bytes, sizeof( BYTE ), outInfo.biSizeImage, file );
	return bytes;
}

Vector4 Bitmap::GetPixel( const Vector2Int& p ) const
{
	auto i = p.x * 3 + p.y * rowSize;
	return Vector4( pixels[i + 2] / 255.f,
					pixels[i + 1] / 255.f,
					pixels[i] / 255.f,
					1.f );
}