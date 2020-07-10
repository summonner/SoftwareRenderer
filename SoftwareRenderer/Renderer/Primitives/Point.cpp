#include "framework.h"
#include "Math/Vector2Int.h"
#include "Point.h"

namespace Renderer
{
	Point::Point( float x, float y, float z )
		: x( x )
		, y( y )
		, z( z )
		, radius( 20 )
	{
	}

	bool Point::Contains( const Vector2Int& coordinate ) const
	{
		auto p = Vector2Int( (int)x, (int)y );
		return p.squaredDistance( coordinate ) < radius;
	}
}