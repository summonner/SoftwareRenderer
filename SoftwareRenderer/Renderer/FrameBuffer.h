#pragma once
#include "PixelIterator.h"

namespace Renderer
{
	class FrameBuffer final
	{
	public:
		FrameBuffer( const HDC dc, const int width, const int height );
		~FrameBuffer();

		void Clear();
		void BitBlt( const HDC dc );
		void SetPixel( const Vector2Int& p, const Vector3& color );

		inline PixelIterator begin() const
		{
			return PixelIterator( info.biWidth, info.biHeight, 0, 0 );
		}

		inline const PixelIterator end() const
		{
			return PixelIterator( info.biWidth, info.biHeight, info.biWidth, info.biHeight );
		}

	private:
		const HDC dc;
		const HBITMAP buffer;
		const BITMAPINFOHEADER info;
		std::unique_ptr<BYTE[]> pixels;
	};
}