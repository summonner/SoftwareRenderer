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
	LineRasterizer::LineRasterizer( std::vector<Vertex>&& vertices )
		: vertices( std::move( vertices ) )
	{
		assert( this->vertices.size() == 2 );
	}

	LineRasterizer::LineRasterizer( const Vertex& a, const Vertex& b )
		: vertices( { a, b } )
	{
	}

	LineRasterizer::~LineRasterizer()
	{
	}

	void LineRasterizer::Rasterize( const Bounds& bounds, const ProcessPixel process )
	{
		auto e = Bresenham( vertices[0], vertices[1] );
		do {
			if ( bounds.Contains( e.p ) == false )
			{
				continue;
			}

			process( RasterizedPixel( e ) );
		} while ( e.Next() );
	}

	bool LineRasterizer::CheckFacet( const CullFunc cullFunc ) const
	{
		return true;
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