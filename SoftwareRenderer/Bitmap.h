#pragma once
#include "Math/Vector4.hpp"
#include "Renderer/PixelIterator.h"
using PixelIterator = Renderer::PixelIterator;

class Bitmap final
{
private:
	Bitmap( BITMAPINFOHEADER info, BYTE* data );

public:
	static std::shared_ptr<Bitmap> Load( LPCTSTR filePath );
	~Bitmap();

	Vector4 GetPixel( const Vector2Int& p ) const;
	Vector4 GetPixel( const Vector2& uv ) const;

	inline PixelIterator begin() const 
	{
		return PixelIterator::begin( width, height );
	}

	inline PixelIterator end() const
	{
		return PixelIterator::end( width, height );
	}


private:
	static BYTE* Parse( FILE* file, BITMAPINFOHEADER& outInfo );
	const int width = 0;
	const int height = 0;
	const int rowSize = 0;
	const std::unique_ptr<BYTE[]> pixels;
};

