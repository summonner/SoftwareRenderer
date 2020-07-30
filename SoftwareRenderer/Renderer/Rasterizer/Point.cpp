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

	void Point::Rasterize( const Bounds& bounds, ProcessPixel process )
	{
		if ( bounds.Contains( v.screen ) == false )
		{
			return;
		}

		const auto values = PixelValues
		{
			v.position.w,
			v.position.z,
			v.color,
			v.texcoord
		};
		process( RasterizedPixel( v.screen, values ) );
	}
}