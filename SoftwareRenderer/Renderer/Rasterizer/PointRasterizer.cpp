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

	void PointRasterizer::PerspectiveDivide( const Matrix4x4& viewport )
	{
		v.PerspectiveDivide( viewport );
	}

	bool PointRasterizer::CheckFacet( CullFunc cullFunc )
	{
		return true;
	}

	void PointRasterizer::Rasterize( const Bounds& bounds, ProcessPixel process )
	{
		if ( bounds.Contains( v.screen ) == false )
		{
			return;
		}

		process( RasterizedPixel( v ) );
	}
}