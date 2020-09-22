#include "framework.h"
#include "Bresenham.h"
#include "../PixelValues.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	Bresenham::Bresenham( const Vertex& a, const Vertex& b, ShadeModel::ShadeFunc shadeFunc )
		: a( a )
		, b( b )
		, diff( b.screen - a.screen )
		, next( diff.x >= 0 ? 1 : -1, diff.y >= 0 ? 1 : -1 )
		, d( 2 * diff.y * next.y - diff.x * next.x )
		, _p( a.screen )
		, CalculateT( (diff.x * next.x) > (diff.y * next.y) ? &Bresenham::CalculateTx : &Bresenham::CalculateTy )
		, t( 0 )
		, p( _p )
		, shadeFunc( shadeFunc != nullptr ? shadeFunc : ShadeModel::SmoothFunc( a.color, b.color ) )
	{
	}

	Bresenham::Bresenham( const Bresenham& source )
		: a( source.a )
		, b( source.b )
		, diff( source.diff )
		, next( source.next )
		, d( source.d )
		, _p( source._p )
		, CalculateT( source.CalculateT )
		, t( source.t )
		, p( _p )
		, shadeFunc( source.shadeFunc )
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
		if ( (y - p.y) >= (b.screen.y - p.y) )
		{
			_p = b.screen;
		}
		else
		{
			while ( y > _p.y || d < 0 )
			{
				MoveNext();
			}
		}

		CalculateParams();
		return t < 1.f;
	}

	void Bresenham::MoveNext()
	{
		if ( d >= 0 )
		{
			_p.y += next.y;
			d -= 2 * diff.x * next.x;
		}

		if ( d <= 0 )
		{
			_p.x += next.x;
			d += 2 * diff.y * next.y;
		}
	}

	void Bresenham::CalculateParams()
	{
		t = CalculateT( *this );
	}

	float Bresenham::CalculateTx() const
	{
		return (_p.x - a.screen.x) / (float)diff.x;
	}

	float Bresenham::CalculateTy() const
	{
		return (_p.y - a.screen.y) / (float)diff.y;
	}

	PixelValues Bresenham::GetValues() const
	{
		return PixelValues
		{
			Lerp( a.position.w, b.position.w, t ),
			Lerp( a.position.z, b.position.z, t ),
			shadeFunc( t ),
			Vector2::Lerp( a.texcoord, b.texcoord, t )
		};
	}

	bool Bresenham::IsXMajor() const
	{
		return abs( diff.x ) > abs( diff.y );
	}
}