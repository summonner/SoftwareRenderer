#include "framework.h"
#include "Bresenham.h"
#include "PixelValues.h"
#include "Renderer/Vertex.h"
#include "ShadeModel.h"

namespace Renderer
{
	Bresenham::Bresenham( const Vertex& a, const Vertex& b, ShadeModel::ShadeFunc shadeFunc )
		: a( a )
		, b( b )
		, diff( b.screen - a.screen )
		, sign( diff.x >= 0 ? 1 : -1, diff.y >= 0 ? 1 : -1 )
		, d( 2 * diff.y * sign.y - diff.x * sign.x )
		, _p( a.screen )
		, CalculateT( (diff.x * sign.x) > (diff.y * sign.y) ? &Bresenham::CalculateTx : &Bresenham::CalculateTy )
		, t( 0 )
		, _w( a.position.w )
		, p( _p )
		, w( _w )
		, shadeFunc( shadeFunc != nullptr ? shadeFunc : ShadeModel::SmoothFunc( a.color, b.color ) )
	{
	}

	Bresenham::Bresenham( const Bresenham& source )
		: a( source.a )
		, b( source.b )
		, diff( source.diff )
		, sign( source.sign )
		, d( source.d )
		, _p( source._p )
		, CalculateT( source.CalculateT )
		, t( source.t )
		, _w( source._w )
		, p( _p )
		, w( _w )
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
			_p.y += sign.y;
			d -= 2 * diff.x * sign.x;
		}

		if ( d <= 0 )
		{
			_p.x += sign.x;
			d += 2 * diff.y * sign.y;
		}
	}

	void Bresenham::CalculateParams()
	{
		t = CalculateT( *this );
		_w = ::Lerp( a.position.w, b.position.w, t );
	}

	float Bresenham::CalculateTx() const
	{
		return (_p.x - a.screen.x) / (float)diff.x;
	}

	float Bresenham::CalculateTy() const
	{
		return (_p.y - a.screen.y) / (float)diff.y;
	}

	Vector4 Bresenham::GetColor() const
	{
		return shadeFunc( t );
	}

	float Bresenham::GetDepth() const
	{
		return ::Lerp( a.position.z, b.position.z, t );
	}

	Vector2 Bresenham::GetTexcoord() const
	{
		return Vector2::Lerp( a.texcoord, b.texcoord, t );
	}

	PixelValues Bresenham::GetValues() const
	{
		return PixelValues
		{
			_w,
			GetDepth(),
			GetColor(),
			GetTexcoord()
		};
	}
}