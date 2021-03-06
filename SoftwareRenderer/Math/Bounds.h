#pragma once
#include "Vector2.hpp"
#include "RangeInt.h"

class PixelIterator;
class Bounds final
{
public:
	Bounds( int width, int height );
	Bounds( const RangeInt& x, const RangeInt& y );

	inline bool Contains( Vector2Int p ) const
	{
		return x.Contains( p.x )
			&& y.Contains( p.y );
	}

	PixelIterator begin() const;
	PixelIterator end() const;

	RangeInt x;
	RangeInt y;
};