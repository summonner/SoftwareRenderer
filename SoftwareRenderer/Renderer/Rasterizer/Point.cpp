#include "framework.h"
#include "Point.h"
#include "Math/Bounds.h"
#include "Renderer/Vertex.h"
#include "RasterizedPixel.h"

namespace Renderer
{
	Point::Point( const Vertex& v )
		: v( v )
	{
	}

	Point::~Point()
	{
	}

	void Point::Rasterize( const Bounds& bounds, ProcessPixel process ) const
	{
		if ( bounds.Contains( v.screen ) == false )
		{
			return;
		}

		process( RasterizedPixel( v.screen, v.color, v.depth ) );
	}
}