#include "framework.h"
#include "Line.h"
#include "Math/Bounds.h"
#include "Bresenham.h"
#include "RasterizedPixel.h"
#include "Renderer/Vertex.h"
#include "Renderer/Rasterizer/Point.h"
#include "DerivativeTexcoord.h"

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

	void Line::Rasterize( const Bounds& bounds, ProcessPixel process )
	{
		const auto derivatives = DerivativeTexcoord::Line( a, b );
		if ( derivatives.IsValid() == false )
		{
			Point( a ).Rasterize( bounds, process );
			return;
		}

		auto e = Bresenham( a, b );
		do {
			if ( bounds.Contains( e.p ) == false )
			{
				continue;
			}

			process( RasterizedPixel( e, derivatives ) );
		} while ( e.Next() );
	}
}