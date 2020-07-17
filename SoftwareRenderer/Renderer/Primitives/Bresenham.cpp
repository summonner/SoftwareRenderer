#include "framework.h"
#include "Bresenham.h"

namespace Renderer
{
	Bresenham::Bresenham( const Vector2Int& a, const Vector2Int& b )
		: b( b )
		, diff( b - a )
		, sign( diff.x >= 0 ? 1 : -1, diff.y >= 0 ? 1 : -1 )
		, d( 2 * diff.y - diff.x )
		, p( a )
	{
	}

	Bresenham::~Bresenham()
	{
	}

	bool Bresenham::Next()
	{
		auto t = (b - p) * sign;
		if ( t.x <= 0 && t.y <= 0 )
		{
			return false;
		}

		if ( d > 0 )
		{
			p.y += sign.y;
			d -= 2 * diff.x * sign.x;
		}

		if ( d <= 0 )
		{
			p.x += sign.x;
			d += 2 * diff.y * sign.y;
		}

		return true;
	}
}