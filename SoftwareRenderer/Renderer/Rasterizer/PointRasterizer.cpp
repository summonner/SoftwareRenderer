#include "framework.h"
#include "PointRasterizer.h"
#include "Math/Bounds.h"
#include "RasterizedPixel.h"

namespace Renderer
{
	PointRasterizer::PointRasterizer( const Vertex& v )
		: v( v )
	{
	}

	PointRasterizer::~PointRasterizer()
	{
	}

	void PointRasterizer::Rasterize( const Matrix4x4& viewport, const Bounds& bounds, ProcessPixel process )
	{
		v.PerspectiveDivide( viewport );

		if ( bounds.Contains( v.screen ) == false )
		{
			return;
		}

		process( RasterizedPixel( v ) );
	}
}