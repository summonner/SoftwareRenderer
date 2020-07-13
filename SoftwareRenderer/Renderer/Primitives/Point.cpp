#include "framework.h"
#include "Point.h"
#include "Math/Vector2.hpp"
#include "Renderer/Vertex.h"

namespace Renderer
{
	Point::Point( const Vertex& v )
		: v( v )
		, radius( 10 )
	{
	}

	bool Point::Contains( const Vector2Int& coordinate ) const
	{
		auto p = v.GetScreenCoordinate();
		return p.SquaredDistance( coordinate ) <= radius * radius;
	}
}