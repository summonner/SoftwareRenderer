#pragma once
#include "Math/Vector.h"

namespace Renderer
{
	class RasterizedPixel;
	class IPrimitive abstract
	{
	public:
		virtual ~IPrimitive() {}

		virtual RasterizedPixel Rasterize( const Vector2& coordinate ) const abstract;
	};
}