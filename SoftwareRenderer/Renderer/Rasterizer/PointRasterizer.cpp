#include "framework.h"
#include "PointRasterizer.h"
#include "Math/Bounds.h"
#include "RasterizedPixel.h"
#include "DerivativeTexcoord.h"

namespace Renderer
{
	PointRasterizer::PointRasterizer( const Vertex& v )
		: v( v )
	{
	}

	PointRasterizer::~PointRasterizer()
	{
	}

	float PointRasterizer::CheckFacet() const
	{
		return 0.f;
	}
	
	DerivativeTexcoord PointRasterizer::Derivative( const bool isTextureEnabled ) const
	{
		return DerivativeTexcoord::invalid;
	}

	void PointRasterizer::Rasterize( const Bounds& bounds, PolygonMode::Mode mode, const ProcessPixel process )
	{
		if ( bounds.Contains( v.screen ) == false )
		{
			return;
		}

		process( RasterizedPixel( v ) );
	}
}