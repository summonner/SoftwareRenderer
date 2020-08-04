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

	bool PointRasterizer::PerspectiveDivide( const Matrix4x4& viewport )
	{
		v.PerspectiveDivide( viewport );
		return true;
	}

	bool PointRasterizer::CheckFacet( const CullFunc cullFunc ) const
	{
		return true;
	}
	
	DerivativeTexcoord PointRasterizer::Derivative( const bool isTextureEnabled ) const
	{
		return DerivativeTexcoord::invalid;
	}

	void PointRasterizer::Rasterize( const Bounds& bounds, const ProcessPixel process )
	{
		if ( bounds.Contains( v.screen ) == false )
		{
			return;
		}

		process( RasterizedPixel( v ) );
	}
}