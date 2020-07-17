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
		Vector2Int v0, v1, v2;
		if ( a.screenCoordinate.y < b.screenCoordinate.y )
		{
			v0 = a.screenCoordinate;
			v1 = b.screenCoordinate;
		}
		else
		{
			v0 = b.screenCoordinate;
			v1 = a.screenCoordinate;
		}

		if ( c.screenCoordinate.y < v0.y )
		{
			v2 = v1;
			v1 = v0;
			v0 = c.screenCoordinate;
		}
		else if ( v1.y < c.screenCoordinate.y )
		{
			v2 = c.screenCoordinate;
		}
		else
		{
			v2 = v1;
			v1 = c.screenCoordinate;
		}

		auto ab = Bresenham( v0, v1 );
		auto ac = Bresenham( v0, v2 );
		auto bc = Bresenham( v1, v2 );

		do {
			pixels.push_back( ab.p );
		} while ( ab.Next() );

		do {
			pixels.push_back( ac.p );
		} while ( ac.Next() );

		do {
			pixels.push_back( bc.p );
		} while ( bc.Next() );
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