#include "framework.h"
#include "RasterizedPixel.h"
#include "Bresenham.h"

namespace Renderer
{
	RasterizedPixel::RasterizedPixel()
		: isValid( false )
		, coordinate( 0, 0 )
		, w( 1 )
		, color( Vector4::zero )
		, depth( 0.0f )
		, texcoord( 0.0f, 0.0f )
	{
	}

	RasterizedPixel::RasterizedPixel( const Vector2Int& coordinate, float w, const Vector4& color, float depth, const Vector2& texcoord )
		: isValid( true )
		, coordinate( coordinate )
		, w( w )
		, color( color )
		, depth( depth )
		, texcoord( texcoord )
	{
	}

	RasterizedPixel::RasterizedPixel( const Bresenham& edge )
		: RasterizedPixel( edge.p, edge.w, edge.GetColor(), edge.GetDepth(), edge.GetTexcoord() )
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