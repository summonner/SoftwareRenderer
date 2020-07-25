#include "framework.h"
#include "Triangle.h"
#include "Renderer/Vertex.h"
#include "Math/RangeInt.h"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Bounds.h"
#include "Bresenham.h"
#include "RasterizedPixel.h"

// ref : http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
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

	void Triangle::Rasterize( const Bounds& bounds, ProcessPixel process ) const
	{
		auto sorted = Sort( a, b, c );

		auto e01 = Bresenham( sorted[0], sorted[1] );
		auto e02 = Bresenham( sorted[0], sorted[2] );
		auto e12 = Bresenham( sorted[1], sorted[2] );
		auto range = bounds.y.Clamp( sorted[0]->screen.y, sorted[2]->screen.y );
		Bounds adjust( bounds.x, range );

		if ( sorted[0]->screen.y == sorted[1]->screen.y )
		{
			Rasterize( adjust, &e02, &e12, &e02, process );
		}
		else if ( sorted[1]->screen.y == sorted[2]->screen.y )
		{
			Rasterize( adjust, &e01, &e02, &e01, process );
		}
		else
		{
			Rasterize( adjust, &e01, &e02, &e12, process );
		}
	}

	void Triangle::Rasterize( const Bounds& bounds, Bresenham* e01, Bresenham* e02, Bresenham* e12, ProcessPixel process )
	{
		auto* e1 = e01;
		auto* e2 = e02;

		for ( auto y : bounds.y )
		{
			while ( e1->p.y < y )
			{
				if ( bounds.Contains( e1->p ) == true )
				{
					process( RasterizedPixel( *e1 ) );
				}

				if ( e1->Next() == false )
				{
					e1 = e12;
				}
			}

			while ( e2->p.y < y )
			{
				if ( bounds.Contains( e2->p ) == true )
				{
					process( RasterizedPixel( *e2 ) );
				}
				e2->Next();
			}

			auto c1 = e1->GetColor();
			auto c2 = e2->GetColor();
			auto d1 = e1->GetDepth();
			auto d2 = e2->GetDepth();
			auto uv1 = e1->GetTexcoord();
			auto uv2 = e2->GetTexcoord();
			
			auto minmax = std::minmax( e1->p.x, e2->p.x );
			float length = (float)(e2->p.x - e1->p.x);
			for ( auto x : bounds.x.Clamp( minmax.first, minmax.second ) )
			{
				auto t = (float)(x - e1->p.x) / length;
				auto w = ::Lerp( e1->w, e2->w, t );
				process( RasterizedPixel( Vector2Int( x, y ), w, Vector4::Lerp( c1, c2, t ), ::Lerp( d1, d2, t ), Vector2::Lerp( uv1, uv2, t ) ) );
			}
		}
	}

	bool AscendingY( const Vertex* l, const Vertex* r )
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