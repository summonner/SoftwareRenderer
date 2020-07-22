#include "framework.h"
#include "Bresenham.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	Bresenham::Bresenham( const Vertex& a, const Vertex& b )
		: a( a )
		, b( b )
		, diff( b.screen - a.screen )
		, sign( diff.x >= 0 ? 1 : -1, diff.y >= 0 ? 1 : -1 )
		, d( 2 * diff.y * sign.y - diff.x * sign.x )
		, p( a.screen )
		, CalculateT( (diff.x * sign.x) > (diff.y * sign.y) ? &Bresenham::CalculateTx : &Bresenham::CalculateTy )
		, t( 0 )
	{
	}

	Bresenham::Bresenham( const Vertex* a, const Vertex* b )
		: Bresenham( *a, *b )
	{
	}

	Bresenham::~Bresenham()
	{
	}

	bool Bresenham::Next()
	{
		if ( t > 1.f )
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
		return (b.screen.x - p.x) / (float)diff.x;
	}

	float Bresenham::CalculateTy() const
	{
		return (b.screen.y - p.y) / (float)diff.y;
	}

	Vector4 Bresenham::GetColor() const
	{
		return Vector4::Lerp( a.color, b.color, t );
	}

	float Bresenham::GetDepth() const
	{
		return ::Lerp( (float)a.depth, (float)b.depth, t );
	}

	Vector2 Bresenham::GetTexcoord() const
	{
		return Vector2::Lerp( a.texcoord, b.texcoord, t );
	}
}