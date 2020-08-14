#pragma once
#include "Util/PixelIterator.h"
#include "Math/Vector4.hpp"
#include "IFrameBuffer.h"

namespace Renderer
{
	class FrameBuffer final : public IFrameBuffer
	{
	public:
		static std::unique_ptr<FrameBuffer> Create( HWND hWnd );
		FrameBuffer( const HDC dc, const int width, const int height );
		~FrameBuffer() override;

		Bounds GetBounds() const override;
		void Reset() override;
		void Clear() override;
		void Clear( const Bounds& bounds ) override;
		void SetClearValue( const Vector4& value ) override;
		void SetColorMask( bool r, bool g, bool b, bool a ) override;
		void SetPixel( const Vector2Int& p, const Vector4& color ) override;
		void SetPixel( const Vector2Int& p, const Vector4& srcColor, std::function<Vector4( const Vector4&, const Vector4& )> blender ) override;
		Vector4 GetPixel( const Vector2Int& p ) const override;

		void BitBlt( const HDC dc );
	private:
		inline int GetIndex( const Vector2Int& p ) const
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
			SetPixel( i, RGBQUAD
			{
				(BYTE)(std::clamp( color.z, 0.f, 1.f ) * 255),
				(BYTE)(std::clamp( color.y, 0.f, 1.f ) * 255),
				(BYTE)(std::clamp( color.x, 0.f, 1.f ) * 255),
				(BYTE)(std::clamp( color.w, 0.f, 1.f ) * 255)
			} );
		}

		inline void SetPixel( const int i, const RGBQUAD& color )
		{
			if ( mask.z ) pixels[i + 0] = color.rgbBlue;
			if ( mask.y ) pixels[i + 1] = color.rgbGreen;
			if ( mask.x ) pixels[i + 2] = color.rgbRed;
			if ( mask.w ) pixels[i + 3] = color.rgbReserved;
		}

	private:
		const HDC dc;
		const HBITMAP buffer;
		const BITMAPINFOHEADER info;

		std::unique_ptr<BYTE[]> pixels;
		RGBQUAD clearValue;
		bool invalidate;
		TVector4<bool> mask;

		static const BYTE colorBytes;
	};
}