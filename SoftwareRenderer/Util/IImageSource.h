#pragma once
#include "PixelIterator.h"

class IImageSource abstract
{
protected:
	IImageSource( int width, int height )
		: width( width )
		, height( height )
	{
	}

public:
	virtual ~IImageSource() {}

	virtual Color4 GetPixel( const Vector2Int& p ) const abstract;

	inline PixelIterator begin() const
	{
		return PixelIterator::begin( width, height );
	}

	inline PixelIterator end() const
	{
		return PixelIterator::end( width, height );
	}

public:
	const int width;
	const int height;
};