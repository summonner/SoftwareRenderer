#include "framework.h"
#include "Triangle.h"
#include "Renderer/Vertex.h"
#include "Math/RangeInt.h"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Bresenham.h"
#include "RasterizedPixel.h"

// ref : http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
namespace Renderer
{
	Triangle::Triangle( const Vertex& a, const Vertex& b, const Vertex& c )
	{
		auto sorted = Sort( a, b, c );

		auto e01 = Bresenham( sorted[0], sorted[1] );
		auto e02 = Bresenham( sorted[0], sorted[2] );
		auto e12 = Bresenham( sorted[1], sorted[2] );
		auto range = RangeInt( std::max( sorted[0]->screen.y, 0 ), sorted[2]->screen.y );

		if ( sorted[0]->screen.y == sorted[1]->screen.y )
		{
			Rasterize( range, &e02, &e12, &e02 );
		}
		else if ( sorted[1]->screen.y == sorted[2]->screen.y )
		{
			Rasterize( range, &e01, &e02, &e01 );
		}
		else
		{
			Rasterize( range, &e01, &e02, &e12 );
		}
	}

	Triangle::~Triangle()
	{
	}

	void Triangle::Rasterize( const RangeInt& range, Bresenham* e01, Bresenham* e02, Bresenham* e12 )
	{
		auto* e1 = e01;
		auto* e2 = e02;

		for ( auto y : range )
		{
			while ( e1->p.y < y )
			{
				pixels.push_back( RasterizedPixel( e1->p, e1->GetColor(), e1->GetDepth() ) );
				if ( e1->Next() == false )
				{
					e1 = e12;
				}
			}

			while ( e2->p.y < y )
			{
				pixels.push_back( RasterizedPixel( e2->p, e2->GetColor(), e2->GetDepth() ) );
				e2->Next();
			}

			auto c1 = e1->GetColor();
			auto c2 = e2->GetColor();
			auto d1 = e1->GetDepth();
			auto d2 = e2->GetDepth();
			auto minmax = std::minmax( e1->p.x, e2->p.x );
			for ( auto x = std::max( minmax.first, 0 ); x <= minmax.second; ++x )
			{
				auto t = (float)(x - e1->p.x) / (float)(e2->p.x - e1->p.x);
				pixels.push_back( RasterizedPixel( Vector2Int( x, y ), Vector4::Lerp( c1, c2, t ), ::Lerp( d1, d2, t ) ) );
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