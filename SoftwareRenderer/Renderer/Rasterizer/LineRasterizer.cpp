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

	void LineRasterizer::Rasterize( const Bounds& bounds, ProcessPixel process, const DerivativeTexcoord& derivatives )
	{
		auto e = Bresenham( vertices[0], vertices[1] );
		do {
			if ( bounds.Contains( e.p ) == false )
			{
				continue;
			}

			process( RasterizedPixel( e, derivatives ) );
		} while ( e.Next() );
	}
}