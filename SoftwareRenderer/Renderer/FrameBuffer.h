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

		inline PixelIterator begin() const
		{
			return PixelIterator( width, height, 0, 0 );
		}

		inline const PixelIterator end() const
		{
			return PixelIterator( width, height, width, height );
		}

	public:
		const HDC dc;
		const HBITMAP buffer;
		const int width;
		const int height;
	};
}