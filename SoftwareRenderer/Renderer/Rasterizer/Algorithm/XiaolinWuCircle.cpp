#include "framework.h"
#include "XiaolinWuCircle.h"
#include "PixelPair.h"

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

	PixelPair XiaolinWuCircle::Get( const Vector2& center ) const
	{
		auto y = center.y + p.y;
		auto yi = (int)y;
		auto min = center.x - p.x;
		auto max = center.x + p.x;

		if ( IsXMajor() == false )
		{
			auto alpha = y - yi;
			if ( p.y < 0 )
			{
				alpha = 1 - alpha;
			}

			return
			{
				PixelPair::Pixel{ (int)min, yi, alpha },
				PixelPair::Pixel{ (int)max, yi, alpha }
			};
		}
		else
		{
			return
			{
				PixelPair::Pixel{ (int)min, yi, 1 - (min - (int)min) },
				PixelPair::Pixel{ (int)max, yi, max - (int)max },
			};
		}
	}
}