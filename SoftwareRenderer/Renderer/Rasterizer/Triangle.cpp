#include "framework.h"
#include "Triangle.h"
#include "Renderer/Vertex.h"
#include "Math/RangeInt.h"
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

	void Triangle::Rasterize( const Bounds& bounds, ProcessPixel process )
	{
		const auto sorted = Sort( a, b, c );
		const Vector2 ab = b.screen - a.screen;
		const Vector2 ac = c.screen - a.screen;
		const auto area = ab.Area( ac );
		const auto dx = Vector2( ac.y, -ab.y ) / area;
		const auto dy = Vector2( -ac.x, ab.x ) / area;
		dw = (b.position.w - a.position.w) * Vector2( dx.x, dy.x ) + (c.position.w - a.position.w) * Vector2( dx.y, dy.y );
		const auto abTexcoord = b.texcoord - a.texcoord;
		const auto acTexcoord = c.texcoord - a.texcoord;
		ddx = abTexcoord * dx.x + acTexcoord * dx.y;
		ddy = abTexcoord * dy.x + acTexcoord * dy.y;

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

		for ( const auto y : bounds.y )
		{
			if ( e1->NextY( y ) == false )
			{
				e1 = e12;
			}

			e2->NextY( y );

			const float length = (float)(e2->p.x - e1->p.x);
			if ( length == 0.f )
			{
				const auto w = e1->w;
				const auto uv = e1->GetTexcoord();
				const auto dFdx = (w * ddx - uv * dw.x) / (w * (w + dw.x));
				const auto dFdy = (w * ddy - uv * dw.y) / (w * (w + dw.y));
				process( RasterizedPixel( e1->p, w, e1->GetColor(), e1->GetDepth(), uv, dFdx, dFdy ) );
				continue;
			}

			const auto c1 = e1->GetColor();
			const auto c2 = e2->GetColor();
			const auto d1 = e1->GetDepth();
			const auto d2 = e2->GetDepth();
			const auto uv1 = e1->GetTexcoord();
			const auto uv2 = e2->GetTexcoord();
			
			const auto minmax = std::minmax( e1->p.x, e2->p.x );
			for ( const auto x : bounds.x.Clamp( minmax.first, minmax.second ) )
			{
				const auto t = (float)(x - e1->p.x) / length;
				const auto w = ::Lerp( e1->w, e2->w, t );
				const auto uv = Vector2::Lerp( uv1, uv2, t );

				const auto dFdx = (w * ddx - uv * dw.x) / (w * (w + dw.x));
				const auto dFdy = (w * ddy - uv * dw.y) / (w * (w + dw.y));
				process( RasterizedPixel( Vector2Int( x, y ), w, Vector4::Lerp( c1, c2, t ), ::Lerp( d1, d2, t ), uv, dFdx, dFdy ) );
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