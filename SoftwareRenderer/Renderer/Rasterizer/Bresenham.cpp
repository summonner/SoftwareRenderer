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
		, w( a.position.w )
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

		MoveNext();
		CalculateParams();
		return t < 1.f;
	}

	bool Bresenham::NextY( const int y )
	{
		while ( y > p.y || d < 0 )
		{
			MoveNext();
		}

		CalculateParams();
		return t < 1.f;
	}

	void Bresenham::MoveNext()
	{
		if ( d >= 0 )
		{
			p.y += sign.y;
			d -= 2 * diff.x * sign.x;
		}

		if ( d <= 0 )
		{
			p.x += sign.x;
			d += 2 * diff.y * sign.y;
		}
	}

	void Bresenham::CalculateParams()
	{
		t = CalculateT( *this );
		w = ::Lerp( a.position.w, b.position.w, t );
	}

	float Bresenham::CalculateTx() const
	{
		return (p.x - a.screen.x) / (float)diff.x;
	}

	float Bresenham::CalculateTy() const
	{
		return (p.y - a.screen.y) / (float)diff.y;
	}

	Vector4 Bresenham::GetColor() const
	{
		return Vector4::Lerp( a.color, b.color, t );
	}

	float Bresenham::GetDepth() const
	{
		return ::Lerp( a.position.z, b.position.z, t );
	}

	Vector2 Bresenham::GetTexcoord() const
	{
		return Vector2::Lerp( a.texcoord, b.texcoord, t );
	}
}