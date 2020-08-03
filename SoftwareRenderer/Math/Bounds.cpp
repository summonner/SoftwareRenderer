#include "framework.h"
#include "Bounds.h"

Bounds::Bounds( int width, int height )
	: x( 0, width )
	, y( 0, height )
{
}

Bounds::Bounds( const RangeInt& x, const RangeInt& y )
	: x( x )
	, y( y )
{
}