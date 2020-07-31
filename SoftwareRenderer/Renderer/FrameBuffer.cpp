#include "framework.h"
#include "FrameBuffer.h"
#include "Math/Vector3.hpp"

namespace Renderer
{
	const int colorBytes = 3;

	FrameBuffer::FrameBuffer( const HDC source, const int width, const int height )
		: dc( CreateCompatibleDC( source ) )
		, buffer( CreateCompatibleBitmap( source, width, height ) )
		, info { sizeof( info ), width, height, 1, colorBytes * 8, BI_RGB, (DWORD)width * height * colorBytes, 0, 0, 0, 0 }
		, pixels( new BYTE[ info.biSizeImage ] )
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
		memset( pixels.get(), 128, sizeof( BYTE ) * info.biSizeImage );
	}

	void FrameBuffer::BitBlt( const HDC source )
	{
		SetDIBits( dc, buffer, 0, info.biWidth, pixels.get(), (const LPBITMAPINFO)&info, DIB_RGB_COLORS );
		::BitBlt( source, 0, 0, info.biWidth, info.biHeight, dc, 0, 0, SRCCOPY );
	}

	void FrameBuffer::SetPixel( const Vector2Int& p, const Vector3& color )
	{
		auto i = (p.x + p.y * info.biWidth) * colorBytes;
		pixels[i + 0] = (BYTE)(color.z * 255);	// B
		pixels[i + 1] = (BYTE)(color.y * 255);	// G
		pixels[i + 2] = (BYTE)(color.x * 255);	// R
	}
}