#include "framework.h"
#include "RasterizedPixel.h"
#include "Bresenham.h"
#include "DerivativeTexcoord.h"

namespace Renderer
{
	RasterizedPixel::RasterizedPixel()
		: isValid( false )
		, coordinate( 0, 0 )
		, w( 1 )
		, color( Vector4::zero )
		, depth( 0.0f )
		, texcoord( 0.0f, 0.0f )
		, ddx( Vector2::zero )
		, ddy( Vector2::zero )
	{
	}

	RasterizedPixel::RasterizedPixel( const Vector2Int& coordinate, float w, const Vector4& color, float depth, const Vector2& texcoord, const DerivativeTexcoord& derivatives )
		: isValid( true )
		, coordinate( coordinate )
		, w( w )
		, color( color )
		, depth( depth )
		, texcoord( texcoord )
		, ddx( derivatives.dFdx( texcoord, w ) )
		, ddy( derivatives.dFdy( texcoord, w ) )
	{
	}

	RasterizedPixel::RasterizedPixel( const Vector2Int& coordinate, float w, const Vector4& color, float depth, const Vector2& texcoord )
		: RasterizedPixel( coordinate, w, color, depth, texcoord, DerivativeTexcoord::invalid )
	{
	}

	RasterizedPixel::RasterizedPixel( const Bresenham& edge, const DerivativeTexcoord& derivatives )
		: RasterizedPixel( edge.p, edge.w, edge.GetColor(), edge.GetDepth(), edge.GetTexcoord(), derivatives )
	{
	}

	RasterizedPixel::~RasterizedPixel()
	{
	}

	const RasterizedPixel RasterizedPixel::discard = RasterizedPixel();

	Vector4 RasterizedPixel::GetColor() const
	{
		return color / w;
	}

	Vector2 RasterizedPixel::GetTexcoord() const
	{
		return texcoord / w;
	}
}