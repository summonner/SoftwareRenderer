#include "framework.h"
#include "XiaolinWu.h"
#include "PixelPair.h"
#include "Renderer/Rasterizer/PixelValues.h"

namespace Renderer
{
	XiaolinWu::XiaolinWu( const Vertex& a, const Vertex& b, const ShadeModel::ShadeFunc shadeFunc )
		: a( a.position )
		, b( b.position )
		, diff( b.position - a.position )
		, isXMajor( abs( diff.y ) < abs( diff.x ) )
		, next( (isXMajor ? diff.x : diff.y) >= 0 ? 1 : -1 )
		, slope( isXMajor ? (diff.y / diff.x) : (diff.x / diff.y) )
		, _p( isXMajor ? (float)a.screen.x : a.position.x + slope * (a.screen.y - a.position.y)
			, isXMajor ? a.position.y + slope * (a.screen.x - a.position.x) : (float)a.screen.y )
		, p( _p )
		, t( 0.f )
		, values( a, b, shadeFunc )
	{
	}

	XiaolinWu::~XiaolinWu()
	{
	}

	bool XiaolinWu::Next()
	{
		if ( isXMajor )
		{
			_p.x += next;
			_p.y += slope * next;
			t = (_p.x - a.x) / diff.x;
		}
		else
		{
			_p.x += slope * next;
			_p.y += next;
			t = (_p.y - a.y) / diff.y;
		}

		return t <= 1.f;
	}

	PixelValues XiaolinWu::GetValues() const
	{
		return values.Get( t );
	}

	bool XiaolinWu::IsXMajor() const
	{
		return isXMajor;
	}

	PixelPair XiaolinWu::Get() const
	{
		auto x = (int)p.x;
		auto y = (int)p.y;
		if ( isXMajor )
		{
			const auto alpha = p.y - (int)p.y;
			return
			{
				PixelPair::Pixel{ x, y, 1 - alpha },
				PixelPair::Pixel{ x, y + 1, alpha },
			};
		}
		else
		{
			const auto alpha = p.x - (int)p.x;
			return 
			{
				PixelPair::Pixel{ x, y, 1 - alpha },
				PixelPair::Pixel{ x + 1, y, alpha },
			};
		}
	}
}