#pragma once
#include "Math/Vector.h"
#include "../RasterizedPixel.h"

namespace Renderer
{
	class IPrimitive abstract
	{
	public:
		virtual ~IPrimitive() {}

		virtual RasterizedPixel Rasterize( const Vector2& coordinate ) const abstract;

	public:
		std::vector<RasterizedPixel> pixels;
	};
}