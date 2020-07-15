#include "framework.h"
#include "Triangle.h"
#include "Renderer/Vertex.h"
#include "Renderer/RasterizedPixel.h"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"

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