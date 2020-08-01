#include "framework.h"
#include "CommonRasterizer.h"
#include "PointRasterizer.h"
#include "DerivativeTexcoord.h"

namespace Renderer
{
	CommonRasterizer::CommonRasterizer( std::vector<Vertex>&& vertices, std::function<DerivativeTexcoord( void )> derivativeBuilder )
		: vertices( std::move( vertices ) )
		, derivativeBuilder( derivativeBuilder )
	{
	}

	CommonRasterizer::~CommonRasterizer()
	{
	}

	void CommonRasterizer::Rasterize( const Matrix4x4& viewport, const Bounds& bounds, ProcessPixel process )
	{
		const auto derivatives = derivativeBuilder();
		if ( derivatives.IsValid() == false )
		{
			PointRasterizer( vertices[0] ).Rasterize( viewport, bounds, process );
			return;
		}

		for ( auto& v : vertices )
		{
			v.PerspectiveDivide( viewport );
		}

		Rasterize( bounds, process, derivatives );
	}
}