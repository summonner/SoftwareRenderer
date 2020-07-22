#include "framework.h"
#include "RasterizedPixel.h"


namespace Renderer
{
	RasterizedPixel::RasterizedPixel()
		: isValid( false )
		, color( Vector4::zero )
		, depth( 0.0f )
		, texcoord( 0.0f, 0.0f )
	{
	}

	RasterizedPixel::RasterizedPixel( const Vector2Int& coordinate, const Vector4& color, float depth, const Vector2& texcoord )
		: isValid( true )
		, coordinate( coordinate )
		, color( color )
		, depth( depth )
		, texcoord( texcoord )
	{
	}

	RasterizedPixel::~RasterizedPixel()
	{
	}

	const RasterizedPixel RasterizedPixel::discard = RasterizedPixel();
}