#pragma once
#include "Math/Vector2.hpp"
#include "Math/Vector4.hpp"
#include "PixelValues.h"

namespace Renderer
{
	class Bresenham;
	class DerivativeTexcoord;
	class RasterizedPixel final
	{
	public:
		RasterizedPixel( const Vector2Int& coordinate, const PixelValues& values, const DerivativeTexcoord& derivatives );
		RasterizedPixel( const Vector2Int& coordinate, const PixelValues& values );
		RasterizedPixel( const Bresenham& edge, const DerivativeTexcoord& derivatives );
		~RasterizedPixel();

		Vector4 GetColor() const;
		Vector2 GetTexcoord() const;
		inline float GetDepth() const
		{
			return values.depth;
		}

		const static RasterizedPixel discard;
	private:
		RasterizedPixel();

	public:
		const bool isValid;
		const Vector2Int coordinate;
		const Vector2 ddx, ddy;

	private:
		const PixelValues values;
	};

}