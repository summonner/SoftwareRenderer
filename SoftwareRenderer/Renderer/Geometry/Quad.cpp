#include "framework.h"
#include "Quad.h"
#include "Renderer/Vertex.h"
#include "Renderer/Clipping/SutherlandHodgman.h"
#include "Renderer/Rasterizer/PolygonRasterizer.h"

namespace Renderer
{
	Quad::Quad( const Vertex& a, const Vertex& b, const Vertex& c, const Vertex& d )
		: a( a )
		, b( b )
		, c( c )
		, d( d )
	{
	}

	Quad::~Quad()
	{
	}

	std::unique_ptr<IRasterizer> Quad::Clip( const Matrix4x4& viewport, const PlaneIterator& planes ) const
	{
		auto vertices = SutherlandHodgman::ClipPolygon( { a, b, c, d }, planes );
		if ( vertices.size() < 3 )
		{
			return nullptr;
		}

		for ( auto& v : vertices )
		{
			v.PerspectiveDivide( viewport );
		}

		return PolygonRasterizer::Create( std::move( vertices ), d.color );
	}
}