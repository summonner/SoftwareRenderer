#pragma once
#include "Renderer/Rasterizer/IRasterizer.h"
#include "Math/Vector2.hpp"

class Bounds;
namespace Renderer
{
	struct PixelValues;
	struct PixelPair
	{
		class Pixel
		{
		public:
			Pixel( int x, int y, float alpha );
			~Pixel();

			void Plot( const Bounds& bounds, const IRasterizer::ProcessPixel process, const PixelValues& values ) const;

			const Vector2Int coord;
			const float alpha;
		};

		Pixel first;
		Pixel second;
	};
}