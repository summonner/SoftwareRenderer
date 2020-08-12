#include "framework.h"
#include "FrameBuffer.h"
#include "Math/Bounds.h"

namespace Renderer
{
	const BYTE FrameBuffer::colorBytes = 4;
	std::unique_ptr<FrameBuffer> FrameBuffer::Create( const HWND hWnd )
	{
		RECT rect;
		GetClientRect( hWnd, &rect );

		auto dc = GetDC( hWnd );
		auto backBuffer = std::make_unique<FrameBuffer>( dc, rect.right, rect.bottom );
		ReleaseDC( hWnd, dc );

		return backBuffer;
	}

	FrameBuffer::FrameBuffer( const HDC source, const int width, const int height )
		: dc( CreateCompatibleDC( source ) )
		, buffer( CreateCompatibleBitmap( source, width, height ) )
		, info{ sizeof( info ), width, height, 1, colorBytes * 8, BI_RGB, (DWORD)width * height * colorBytes, 0, 0, 0, 0 }
		, pixels( new BYTE[info.biSizeImage] )
		, clearValue{ 0, 0, 0, 0 }
		, invalidate( false )
	{
		SelectObject( dc, buffer );
		GetDIBits( dc, buffer, 0, info.biHeight, (LPVOID)pixels.get(), (LPBITMAPINFO)&info, DIB_RGB_COLORS );
	}

	FrameBuffer::~FrameBuffer()
	{
		DeleteObject( buffer );
		DeleteDC( dc );
	}

	Bounds FrameBuffer::GetBounds() const
	{
		return Bounds( (int)info.biWidth, (int)info.biHeight );
	}

	void FrameBuffer::Reset()
	{
		clearValue = RGBQUAD { 0, 0, 0, 0 };
	}

	void FrameBuffer::Clear()
	{
		invalidate = true;
	}

	void FrameBuffer::Clear( const Bounds& viewport )
	{
		if ( invalidate == false )
		{
			return;
		}

		for ( auto p : viewport )
		{
			const auto i = (p.x + p.y * info.biWidth) * colorBytes;
			memcpy( pixels.get() + i, &clearValue, colorBytes );
		}

		invalidate = false;
	}

	void FrameBuffer::SetClearValue( const Vector4& value )
	{
		clearValue.rgbRed =  (BYTE)(value.x * 255);
		clearValue.rgbGreen = (BYTE)(value.y * 255);
		clearValue.rgbBlue = (BYTE)(value.z * 255);
		clearValue.rgbReserved = (BYTE)(value.w * 255);
	}

	void FrameBuffer::BitBlt( const HDC source )
	{
		SetDIBits( dc, buffer, 0, info.biWidth, pixels.get(), (const LPBITMAPINFO)&info, DIB_RGB_COLORS );
		::BitBlt( source, 0, 0, info.biWidth, info.biHeight, dc, 0, 0, SRCCOPY );
	}

	void FrameBuffer::SetPixel( const Vector2Int& p, const Vector4& color )
	{
		const auto i = GetIndex( p );
		SetPixel( i, color );
	}

	void FrameBuffer::SetPixel( const Vector2Int& p, const Vector4& srcColor, std::function<Vector4( const Vector4&, const Vector4& )> blender )
	{
		Vector4 result;
		const auto i = GetIndex( p );
		if ( blender == nullptr )
		{
			result = srcColor;
		}
		else
		{
			const auto dstColor = GetPixel( i );
			result = blender( srcColor, dstColor );
		}

		SetPixel( i, result );
	}

	Vector4 FrameBuffer::GetPixel( const Vector2Int& p ) const
	{
		const auto i = GetIndex( p );
		return GetPixel( i );
	}
}