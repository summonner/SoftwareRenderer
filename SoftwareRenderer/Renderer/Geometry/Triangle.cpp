#include "framework.h"
#include "Triangle.h"
#include "Renderer/Vertex.h"
#include "SutherlanHodgmanClipping.h"
#include "Renderer/Rasterizer/PolygonRasterizer.h"

namespace Renderer
{
	Triangle::Triangle( const Vertex& a, const Vertex& b, const Vertex& c )
		: a( a )
		, b( b )
		, c( c )
	{
	}

	Triangle::~Triangle()
	{
	}

	std::unique_ptr<IRasterizer> Triangle::Clip() const
	{
		auto vertices = SutherlandHodgmanClipping::Clip( { a, b, c } );
		if ( vertices.size() < 3 )
		{
			return nullptr;
		}

		auto derivatives = [&]() { return Derivative(); };
		return std::make_unique<PolygonRasterizer>( std::move( vertices ), derivatives );
	}

	DerivativeTexcoord Triangle::Derivative() const
	{
		return DerivativeTexcoord::Triangle( a, b, c );
	}
}