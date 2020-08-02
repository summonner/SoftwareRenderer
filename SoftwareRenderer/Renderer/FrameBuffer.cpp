#include "framework.h"
#include "FrameBuffer.h"
#include "Math/Vector4.hpp"

namespace Renderer
{
	const int colorBytes = 3;

	FrameBuffer::FrameBuffer( const HDC source, const int width, const int height )
		: dc( CreateCompatibleDC( source ) )
		, buffer( CreateCompatibleBitmap( source, width, height ) )
		, info{ sizeof( info ), width, height, 1, colorBytes * 8, BI_RGB, (DWORD)width * height * colorBytes, 0, 0, 0, 0 }
		, pixels( new BYTE[info.biSizeImage] )
		, clearValue{ 0, 0, 0, 0 }
	{
		SelectObject( dc, buffer );
		GetDIBits( dc, buffer, 0, info.biHeight, (LPVOID)pixels.get(), (LPBITMAPINFO)&info, DIB_RGB_COLORS );
	}


	FrameBuffer::~FrameBuffer()
	{
		DeleteObject( buffer );
		DeleteDC( dc );
	}

	void FrameBuffer::Clear()
	{
		for ( auto i = 0u; i < info.biSizeImage; i += colorBytes )
		{
			memcpy( pixels.get() + i, &clearValue, sizeof( RGBTRIPLE ) );
		}
	}

	void FrameBuffer::SetClearValue( const Vector4& value )
	{
		clearValue.rgbRed =  (BYTE)(value.x * 255);
		clearValue.rgbBlue = (BYTE)(value.y * 255);
		clearValue.rgbGreen = (BYTE)(value.y * 255);
		clearValue.rgbReserved = (BYTE)(value.y * 255);
	}

	void FrameBuffer::BitBlt( const HDC source )
	{
		SetDIBits( dc, buffer, 0, info.biWidth, pixels.get(), (const LPBITMAPINFO)&info, DIB_RGB_COLORS );
		::BitBlt( source, 0, 0, info.biWidth, info.biHeight, dc, 0, 0, SRCCOPY );
	}

	void FrameBuffer::SetPixel( const Vector2Int& p, const Vector4& color )
	{
		auto i = (p.x + p.y * info.biWidth) * colorBytes;
		pixels[i + 0] = (BYTE)(color.z * 255);	// B
		pixels[i + 1] = (BYTE)(color.y * 255);	// G
		pixels[i + 2] = (BYTE)(color.x * 255);	// R
	}
}