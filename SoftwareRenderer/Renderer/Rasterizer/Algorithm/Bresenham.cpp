#include "framework.h"
#include "Bresenham.h"
#include "../PixelValues.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	Bresenham::Bresenham( const Vertex& a, const Vertex& b, ShadeModel::ShadeFunc shadeFunc )
		: Bresenham( a.screen, b.screen, VertexInterpolator( a, b, shadeFunc ) )
	{
	}

	Bresenham::Bresenham( const Vector2Int& a, const Vector2Int& b, const VertexInterpolator& values )
		: a( a )
		, b( b )
		, diff( b - a )
		, next( diff.x >= 0 ? 1 : -1, diff.y >= 0 ? 1 : -1 )
		, d( 2 * diff.y * next.y - diff.x * next.x )
		, _p( a )
		, CalculateT( (diff.x* next.x) > (diff.y* next.y) ? &Bresenham::CalculateTx : &Bresenham::CalculateTy )
		, t( 0 )
		, p( _p )
		, values( values )
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
		, values( source.values )
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
		if ( (y - p.y) >= (b.y - p.y) )
		{
			_p = b;
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
		return (_p.x - a.x) / (float)diff.x;
	}

	float Bresenham::CalculateTy() const
	{
		return (_p.y - a.y) / (float)diff.y;
	}

	PixelValues Bresenham::GetValues() const
	{
		return values.Get( t );
	}

	bool Bresenham::IsXMajor() const
	{
		return abs( diff.x ) > abs( diff.y );
	}
}