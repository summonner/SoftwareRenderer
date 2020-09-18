#include "framework.h"
#include "Triangle.h"
#include "Renderer/Vertex.h"
#include "Renderer/Clipping/SutherlandHodgman.h"
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

	std::unique_ptr<IRasterizer> Triangle::Clip( const Matrix4x4& viewport, const PlaneIterator& planes ) const
	{
		auto vertices = SutherlandHodgman::ClipPolygon( { a, b, c }, planes );
		if ( vertices.size() < 3 )
		{
			return nullptr;
		}

		for ( auto& v : vertices )
		{
			v.PerspectiveDivide( viewport );
		}

		return PolygonRasterizer::Create( std::move( vertices ), c.color );
	}
}