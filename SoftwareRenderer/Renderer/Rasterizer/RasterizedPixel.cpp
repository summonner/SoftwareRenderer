#include "framework.h"
#include "RasterizedPixel.h"


namespace Renderer
{
	RasterizedPixel::RasterizedPixel()
		: isValid( false )
		, color( Vector4::zero )
		, depth( 0.0f )
	{
	}

	RasterizedPixel::RasterizedPixel( const Vector4& color, float depth )
		: RasterizedPixel( Vector2Int::zero, color, depth )
	{
	}

	RasterizedPixel::RasterizedPixel( const Vector2Int& coordinate, const Vector4& color, float depth )
		: isValid( true )
		, coordinate( coordinate )
		, color( color )
		, depth( depth )
	{
	}

	RasterizedPixel::~RasterizedPixel()
	{
	}

	const RasterizedPixel RasterizedPixel::discard = RasterizedPixel();
}