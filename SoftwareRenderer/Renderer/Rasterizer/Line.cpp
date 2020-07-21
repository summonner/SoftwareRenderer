#include "framework.h"
#include "Line.h"
#include "Math/Bounds.h"
#include "Bresenham.h"
#include "RasterizedPixel.h"

namespace Renderer
{
	Line::Line( const Vertex& a, const Vertex& b )
		: a( a )
		, b( b )
	{

	}

	Line::~Line()
	{
	}

	void Line::Rasterize( const Bounds& bounds, ProcessPixel process ) const
	{
		auto e = Bresenham( a, b );
		do {
			if ( bounds.Contains( e.p ) == false )
			{
				continue;
			}

			process( RasterizedPixel( e.p, e.GetColor(), e.GetDepth() ) );
		} while ( e.Next() );
	}
}