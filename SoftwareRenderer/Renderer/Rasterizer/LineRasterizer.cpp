#include "framework.h"
#include "LineRasterizer.h"
#include "Math/Bounds.h"
#include "Bresenham.h"
#include "RasterizedPixel.h"
#include "Renderer/Vertex.h"
#include "Renderer/Rasterizer/PointRasterizer.h"
#include "DerivativeTexcoord.h"

namespace Renderer
{
	LineRasterizer::LineRasterizer( std::vector<Vertex>&& vertices, ShadeModel::ShadeFunc shadeFunc )
		: vertices( std::move( vertices ) )
		, shadeFunc( shadeFunc )
	{
		assert( this->vertices.size() == 2 );
	}

	LineRasterizer::LineRasterizer( const Vertex& a, const Vertex& b, ShadeModel::ShadeFunc shadeFunc )
		: vertices( { a, b } )
		, shadeFunc( shadeFunc )
	{
	}

	LineRasterizer::~LineRasterizer()
	{
	}

	void LineRasterizer::Rasterize( const Bounds& bounds, PolygonMode::Mode mode, const ProcessPixel process )
	{
		auto e = Bresenham( vertices[0], vertices[1], shadeFunc );
		do {
			if ( bounds.Contains( e.p ) == false )
			{
				continue;
			}

			process( RasterizedPixel( e ) );
		} while ( e.Next() );
	}

	float LineRasterizer::CheckFacet() const
	{
		return 0.f;
	}

	DerivativeTexcoord LineRasterizer::Derivative( const bool isTextureEnabled ) const
	{
		if ( isTextureEnabled == false )
		{
			return DerivativeTexcoord::invalid;
		}

		return DerivativeTexcoord::Line( vertices[0], vertices[1] );
	}
}