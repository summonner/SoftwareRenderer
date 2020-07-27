#include "framework.h"
#include "Line.h"
#include "Math/Bounds.h"
#include "Bresenham.h"
#include "RasterizedPixel.h"
#include "Renderer/Vertex.h"
#include "Renderer/Rasterizer/Point.h"

namespace Renderer
{
	Line::Line( const Vertex& a, const Vertex& b )
		: a( a )
		, b( b )
	{

	}

	Line::~Line()
	{
	}

	void Line::Rasterize( const Bounds& bounds, ProcessPixel process ) const
	{
		const Vector2 d = b.screen - a.screen;
		const auto denom = d.x * d.x + d.y * d.y;
		if ( denom == 0.f )
		{
			Point( a ).Rasterize( bounds, process );
			return;
		}

		const Vector2 t( d.x / denom, d.y / denom );
		const Vector2 duv = b.texcoord - a.texcoord;
		const Vector2 ddx = duv * t.x;
		const Vector2 ddy = duv * t.y;
		const Vector2 dw = (b.position.w - a.position.w) * t;

		auto e = Bresenham( a, b );
		do {
			if ( bounds.Contains( e.p ) == false )
			{
				continue;
			}

			const auto uv = e.GetTexcoord();
			const auto dFdx = (e.w * ddx - dw.x * uv) / (e.w * (e.w + dw.x));
			const auto dFdy = (e.w * ddy - dw.y * uv) / (e.w * (e.w + dw.y));
			process( RasterizedPixel( e.p, e.w, e.GetColor(), e.GetDepth(), uv, dFdx, dFdy ) );
		} while ( e.Next() );
	}
}