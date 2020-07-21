#include "framework.h"
#include "Bounds.h"

Bounds::Bounds( int width, int height )
	: x( 0, width - 1 )
	, y( 0, height - 1 )
{
}

Bounds::Bounds( const RangeInt& x, const RangeInt& y )
	: x( x )
	, y( y )
{
}