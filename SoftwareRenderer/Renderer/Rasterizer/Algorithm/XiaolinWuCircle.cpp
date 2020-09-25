#include "framework.h"
#include "XiaolinWuCircle.h"

namespace Renderer
{
	const float XiaolinWuCircle::invSqrt2 = 1.f / sqrt( 2.f );
	XiaolinWuCircle::XiaolinWuCircle( float radius )
		: rr( radius* radius )
		, _p( 0, -radius )
		, p( _p )
		, m( (int)(radius * invSqrt2) )
	{
	}

	XiaolinWuCircle::~XiaolinWuCircle()
	{
	}

	bool XiaolinWuCircle::Next()
	{
		if ( _p.x < 0 )
		{
			return false;
		}
		
		if ( _p.x >= m )
		{
			_p.y += 1;
			_p.x = sqrt( rr - _p.y * _p.y );
		}
		else
		{
			const auto sign = _p.y < 0 ? -1 : 1;
			_p.x += -sign;
			_p.y = sqrt( rr - p.x * _p.x ) * sign;
		}

		return true;
	}

	bool XiaolinWuCircle::IsXMajor() const
	{
		return _p.x >= m;
	}
}