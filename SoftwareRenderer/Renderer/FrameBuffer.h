#pragma once
#include "PixelIterator.h"
#include "Math/Vector4.hpp"

namespace Renderer
{
	class FrameBuffer final
	{
	public:
		FrameBuffer( const HDC dc, const int width, const int height );
		~FrameBuffer();

		void Reset();
		void Clear();
		void SetClearValue( const Vector4& value );
		void BitBlt( const HDC dc );
		void SetPixel( const Vector2Int& p, const Vector4& color );
		void SetPixel( const Vector2Int& p, const Vector4& srcColor, std::function<Vector4( const Vector4&, const Vector4& )> blender );

		inline PixelIterator begin() const
		{
			return PixelIterator( info.biWidth, info.biHeight, 0, 0 );
		}

		inline const PixelIterator end() const
		{
			return PixelIterator( info.biWidth, info.biHeight, info.biWidth - 1, info.biHeight - 1 );
		}

	private:
		inline int GetIndex( const Vector2Int& p )
		{
			return (p.x + p.y * info.biWidth) * colorBytes;
		}

		inline Vector4 GetPixel( const int i ) const
		{
			return Vector4(
				pixels[i + 2] / 255.f,
				pixels[i + 1] / 255.f,
				pixels[i + 0] / 255.f,
				pixels[i + 3] / 255.f
			);
		}
		
		inline void SetPixel( const int i, const Vector4& color )
		{
			pixels[i + 0] = (BYTE)(std::clamp( color.z, 0.f, 1.f ) * 255);	// B
			pixels[i + 1] = (BYTE)(std::clamp( color.y, 0.f, 1.f ) * 255);	// G
			pixels[i + 2] = (BYTE)(std::clamp( color.x, 0.f, 1.f ) * 255);	// R
			pixels[i + 3] = (BYTE)(std::clamp( color.w, 0.f, 1.f ) * 255);	// A
		}

	private:
		const HDC dc;
		const HBITMAP buffer;
		const BITMAPINFOHEADER info;
		std::unique_ptr<BYTE[]> pixels;
		RGBQUAD clearValue;

		static const BYTE colorBytes;
	};
}