#include "framework.h"
#include "PixelIterator.h"

PixelIterator::PixelIterator( const Bounds& bounds, int x, int y )
	: bounds( bounds )
	, current( x, y )
{
}

bool PixelIterator::operator !=( const PixelIterator& other ) const
{
	return current != other.current;
}

const PixelIterator& PixelIterator::operator ++()
{
	if ( current.x < bounds.x.max - 1 )
	{
		current.x += 1;
	}
	else
	{
		current.x = bounds.x.min;
		current.y += 1;
	}

	return *this;
}

Vector2Int PixelIterator::operator *() const
{
	return current;
}