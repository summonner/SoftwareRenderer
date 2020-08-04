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
		: CommonRasterizer( std::move( vertices ) )
	{
		assert( this->vertices.size() == 2 );
	}

	LineRasterizer::~LineRasterizer()
	{
	}

	bool LineRasterizer::PostPerspectiveDivide()
	{
		return vertices[0].screen != vertices[1].screen;
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