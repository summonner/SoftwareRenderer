#include "framework.h"
#include "Triangle.h"
#include "Renderer/Vertex.h"
#include "Math/RangeInt.h"
#include "Math/Vector3.hpp"
#include "Math/Bounds.h"
#include "RasterizedPixel.h"
#include "DerivativeTexcoord.h"
#include "Point.h"
#include "BresenhamList.h"
#include "PixelValues.h"

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

	void Triangle::Rasterize( const Bounds& bounds, ProcessPixel process )
	{
		const auto derivatives = DerivativeTexcoord::Triangle( a, b, c );
		if ( derivatives.IsValid() == false )
		{
			Point( a ).Rasterize( bounds, process );
			return;
		}

		const auto sorted = Sort( a, b, c );
		auto range = bounds.y.Clamp( sorted[0]->screen.y, sorted[2]->screen.y );
		Bounds adjust( bounds.x, range );
		BresenhamList e1 { sorted[0], sorted[1], sorted[2] };
		BresenhamList e2 { sorted[0], sorted[2] };
		Rasterize( adjust, e1, e2, process, derivatives );
	}

	void Triangle::Rasterize( const Bounds& bounds, BresenhamList& e1, BresenhamList& e2, ProcessPixel process, const DerivativeTexcoord& derivatives )
	{
		for ( const auto y : bounds.y )
		{
			e1.NextY( y );
			e2.NextY( y );

			const float length = (float)(e2.x - e1.x);
			if ( length == 0.f )
			{
				process( RasterizedPixel( e1.GetCurrent(), derivatives ) );
				continue;
			}

			const auto values1 = e1.GetValues();
			const auto values2 = e2.GetValues();
			
			const auto minmax = std::minmax( e1.x, e2.x );
			for ( const auto x : bounds.x.Clamp( minmax.first, minmax.second ) )
			{
				const auto t = (float)(x - e1.x) / length;
				const auto values = PixelValues::Lerp( values1, values2, t );
				process( RasterizedPixel( Vector2Int( x, y ), values, derivatives ) );
			}
		}
	}

	bool Triangle::AscendingY( const Vertex* l, const Vertex* r )
	{
		return l->screen.y < r->screen.y;
	}

	std::vector<const Vertex*> Triangle::Sort( const Vertex& a, const Vertex& b, const Vertex& c )
	{
		std::vector<const Vertex*> sorted( 3 );
		sorted[0] = &a;
		sorted[1] = &b;
		sorted[2] = &c;

		sort( sorted.begin(), sorted.end(), AscendingY );
		return sorted;
	}
}