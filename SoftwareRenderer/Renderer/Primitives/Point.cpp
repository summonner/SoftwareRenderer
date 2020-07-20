#include "framework.h"
#include "Point.h"
#include "Math/Vector2.hpp"
#include "Renderer/Vertex.h"
#include "Renderer/RasterizedPixel.h"

namespace Renderer
{
	Point::Point( const Vertex& v )
		: v( v )
		, radius( 10 )
	{
	}

	Point::~Point()
	{
	}

	bool Point::Contains( const Vector2& coordinate ) const
	{
		auto p = v.screen;
		return p.SquaredDistance( coordinate ) <= radius * radius;
	}

	RasterizedPixel Point::Rasterize( const Vector2& coordinate ) const
	{
		if ( Contains( coordinate ) == false )
		{
			return RasterizedPixel::discard;
		}

		return RasterizedPixel( v.color, v.position.z );
	}
}