#pragma once
#include "Math/Vector4.hpp"
#include "IImageSource.h"
#include "Renderer/Texturing/ITexture.h"

class Bitmap final : public IImageSource, public Renderer::ITexture
{
private:
	Bitmap( BITMAPINFOHEADER info, BYTE* data, RGBQUAD* palette );

public:
	static std::shared_ptr<Bitmap> Load( LPCTSTR filePath );
	~Bitmap();

	Color4 GetPixel( const Vector2Int& p ) const override;
	Vector4 GetPixel( const Vector2& uv ) const override;

private:
	static std::shared_ptr<Bitmap> Parse( FILE* file );
	static RGBQUAD* ParsePalette( FILE* file, BITMAPINFOHEADER& info );
	static const WORD BM = 0x4D42;

private:
	const int rowSize = 0;
	const int pixelSize = 0;
	const std::unique_ptr<BYTE[]> pixels;
	const std::unique_ptr<RGBQUAD[]> palette;
};

