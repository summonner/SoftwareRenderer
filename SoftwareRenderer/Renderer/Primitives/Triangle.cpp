#include "framework.h"
#include "Triangle.h"
#include "Renderer/Vertex.h"
#include "Math/Vector2.hpp"

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

	bool Triangle::Contains( const Vector2Int& coordinate ) const
	{
		auto bary = Barycentric( coordinate );
		return (bary.y >= 0.f)
			&& (bary.z >= 0.f)
			&& ((bary.y + bary.z) <= 1.f);
	}

	Vector3 Triangle::Barycentric( const Vector2Int& p ) const
	{
		auto a = this->a.GetScreenCoordinate();
		auto b = this->b.GetScreenCoordinate();
		auto c = this->c.GetScreenCoordinate();

		auto ab = b - a;
		auto ac = c - a;
		auto m = ab.Area( ac );

		auto cb = b - c;
		auto u = (p - b).Area( cb ) / m;
		auto v = (p - c).Area( ac ) / m;
		return Vector3( u, v, 1.f - u - v );
	}
}