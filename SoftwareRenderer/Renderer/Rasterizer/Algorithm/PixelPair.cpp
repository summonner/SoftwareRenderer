#include "framework.h"
#include "PixelPair.h"
#include "Math/Bounds.h"
#include "Renderer/Rasterizer/PixelValues.h"
#include "Renderer/Rasterizer/RasterizedPixel.h"

namespace Renderer
{
	PixelPair::Pixel::Pixel( int x, int y, float alpha )
		: coord( x, y )
		, alpha( alpha )
	{
	}

	PixelPair::Pixel::~Pixel()
	{
	}

	void PixelPair::Pixel::Plot( const Bounds& bounds, const IRasterizer::ProcessPixel process, const PixelValues& values ) const
	{
		if ( bounds.Contains( coord ) == false )
		{
			return;
		}

		process( RasterizedPixel::AdditionalAlpha( coord, values, alpha ) );
	}
}