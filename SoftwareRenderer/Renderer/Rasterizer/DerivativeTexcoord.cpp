#include "framework.h"
#include "DerivativeTexcoord.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	DerivativeTexcoord::DerivativeTexcoord( const float denom, const Vector2& dw, const Vector2& ddx, const Vector2& ddy )
		: denom( denom )
		, dw( dw )
		, ddx( ddx )
		, ddy( ddy )
	{
	}

	DerivativeTexcoord DerivativeTexcoord::Line( const Vertex& a, const Vertex& b )
	{
		const Vector2 dxy = b.screen - a.screen;
		const auto denom = dxy.x * dxy.x + dxy.y * dxy.y;
		if ( denom == 0 )
		{
			return DerivativeTexcoord::invalid;
		}

		const Vector2 dt_dxy( dxy.x / denom, dxy.y / denom );
		const Vector2 duv_dt = b.texcoord - a.texcoord;
		const Vector2 duv_dx = duv_dt * dt_dxy.x;
		const Vector2 duv_dy = duv_dt * dt_dxy.y;
		const Vector2 dw_dxy = (b.position.w - a.position.w) * dt_dxy;

		return DerivativeTexcoord( denom, dw_dxy, duv_dx, duv_dy );
	}

	DerivativeTexcoord DerivativeTexcoord::Triangle( const Vertex& a, const Vertex& b, const Vertex& c )
	{
		const Vector2 ab = b.screen - a.screen;
		const Vector2 ac = c.screen - a.screen;
		const auto area = ab.Area( ac );
		if ( area == 0 )
		{
			return DerivativeTexcoord::invalid;
		}

		const auto dst_dx = Vector2( ac.y, -ab.y ) / area;
		const auto dst_dy = Vector2( -ac.x, ab.x ) / area;
		const auto dw_dxy = (b.position.w - a.position.w) * Vector2( dst_dx.x, dst_dy.x ) + (c.position.w - a.position.w) * Vector2( dst_dx.y, dst_dy.y );
		const auto duv_ds = b.texcoord - a.texcoord;
		const auto duv_dt = c.texcoord - a.texcoord;
		const auto duv_dx = duv_ds * dst_dx.x + duv_dt * dst_dx.y;
		const auto duv_dy = duv_ds * dst_dy.x + duv_dt * dst_dy.y;

		return DerivativeTexcoord( area, dw_dxy, duv_dx, duv_dy );
	}

	DerivativeTexcoord::~DerivativeTexcoord()
	{
	}

	Vector2 DerivativeTexcoord::dFdx( const Vector2& uv, const float w ) const
	{
		if ( IsValid() == false )
		{
			return Vector2::zero;
		}

		return (w * ddx - uv * dw.x) / (w * (w + dw.x));
	}

	Vector2 DerivativeTexcoord::dFdy( const Vector2& uv, const float w ) const
	{
		if ( IsValid() == false )
		{
			return Vector2::zero;
		}

		return (w * ddy - uv * dw.y) / (w * (w + dw.y));
	}

	const DerivativeTexcoord DerivativeTexcoord::invalid( 0, Vector2::zero, Vector2::zero, Vector2::zero );
}