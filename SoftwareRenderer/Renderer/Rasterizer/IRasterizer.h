#pragma once
#include "Math/Vector.h"
#include "RasterizedPixel.h"

namespace Renderer
{
	class IRasterizer abstract
	{
	public:
		virtual ~IRasterizer() {}

	public:
		std::vector<RasterizedPixel> pixels;
	};
}