#include "framework.h"
#include "PixelIterator.h"


PixelIterator::PixelIterator( int width, int height, int x, int y )
	: width( width )
	, height( height )
	, current( x, y )
{
}

bool PixelIterator::operator !=( const PixelIterator& other ) const
{
	return current != other.current;
}

const PixelIterator& PixelIterator::operator ++()
{
	if ( current.x < width )
	{
		current.x += 1;
	}
	else if ( current.y < height )
	{
		current.x = 0;
		current.y += 1;
	}

	return *this;
}

Vector2Int PixelIterator::operator *() const
{
	return current;
}
