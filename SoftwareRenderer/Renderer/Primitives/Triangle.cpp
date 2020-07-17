#include "framework.h"
#include "Triangle.h"
#include "Renderer/Vertex.h"
#include "Renderer/RasterizedPixel.h"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Bresenham.h"

namespace Renderer
{
	Triangle::Triangle( const Vertex& a, const Vertex& b, const Vertex& c )
		: a( a )
		, b( b )
		, c( c )
	{
		auto sorted = Sort( a, b, c );

		auto ab = Bresenham( sorted[0]->screenCoordinate, sorted[1]->screenCoordinate );
		auto ac = Bresenham( sorted[0]->screenCoordinate, sorted[2]->screenCoordinate );
		auto bc = Bresenham( sorted[1]->screenCoordinate, sorted[2]->screenCoordinate );

		do {
			pixels.push_back( RasterizedPixel( ab.p, Vector4::Lerp( sorted[0]->color, sorted[1]->color, ab.t), 1 ) );
		} while ( ab.Next() );

		do {
			pixels.push_back( RasterizedPixel( ac.p, Vector4::Lerp( sorted[0]->color, sorted[2]->color, ac.t ), 1 ) );
		} while ( ac.Next() );

		do {
			pixels.push_back( RasterizedPixel( bc.p, Vector4::Lerp( sorted[1]->color, sorted[2]->color, bc.t ), 1 ) );
		} while ( bc.Next() );
	}

	std::vector<const Vertex*> Triangle::Sort( const Vertex& a, const Vertex& b, const Vertex& c )
	{
		std::vector<const Vertex*> sorted( 3 );
		sorted[0] = &a;
		sorted[1] = &b;
		sorted[2] = &c;

		sort( sorted.begin(), sorted.end(), []( const Vertex* l, const Vertex* r ) { return l->screenCoordinate.y < r->screenCoordinate.y; } );
		return sorted;
	}

	Triangle::~Triangle()
	{
	}

	Vector3 Triangle::Barycentric( const Vector2& p ) const
	{
		auto a = this->a.screenCoordinate;
		auto b = this->b.screenCoordinate;
		auto c = this->c.screenCoordinate;

		auto ab = b - a;
		auto ac = c - a;
		auto m = ab.Area( ac );

		auto cb = b - c;
		auto u = (p - b).Area( cb ) / m;
		auto v = (p - c).Area( ac ) / m;
		return Vector3( u, v, 1.f - u - v );
	}

	RasterizedPixel Triangle::Rasterize( const Vector2& coordinate ) const
	{
		auto bary = Barycentric( coordinate );
		auto isDiscard = (bary.y >= 0.f)
					  && (bary.z >= 0.f)
					  && ((bary.y + bary.z) <= 1.f);
		if ( isDiscard == false )
		{
			return RasterizedPixel::discard;
		}

		return Lerp( bary );
	}

	RasterizedPixel Triangle::Lerp( const Vector3& barycentric ) const
	{
		auto color = a.color * barycentric.x + b.color * barycentric.y + c.color * barycentric.z;
		auto depth = barycentric.Dot( Vector3( a.position.z, b.position.z, c.position.z ) );
		return RasterizedPixel( color, depth );
	}
}