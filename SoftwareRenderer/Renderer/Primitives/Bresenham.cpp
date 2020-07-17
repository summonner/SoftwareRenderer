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
		, CalculateT( diff.x > diff.y ? &Bresenham::CalculateTx : &Bresenham::CalculateTy )
		, t( 1 )
	{
	}

	Bresenham::~Bresenham()
	{
	}

	bool Bresenham::Next()
	{
		if ( t <= 0.f )
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

		t = 1 - CalculateT( *this );
		return t < 1.f;
	}

	float Bresenham::CalculateTx() const
	{
		return (b.x - p.x) / (float)diff.x;
	}

	float Bresenham::CalculateTy() const
	{
		return (b.y - p.y) / (float)diff.y;
	}
}