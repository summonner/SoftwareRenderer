#pragma once
#include "Math/Vector2.hpp"
#include "Math/Vector4.hpp"
#include "PixelValues.h"

namespace Renderer
{
	class Bresenham;
	class DerivativeTexcoord;
	class Vertex;
	class RasterizedPixel final
	{
	private:
		RasterizedPixel();
	public:
		RasterizedPixel( const Vector2Int& coordinate, const PixelValues& values );
		RasterizedPixel( int x, int y, const PixelValues& values );
		RasterizedPixel( const Bresenham& edge );
		RasterizedPixel( const Vertex& vertex );
		~RasterizedPixel();

		Vector4 GetColor() const;
		Vector2 GetTexcoord() const;
		inline float GetDepth() const
		{
			return values.depth;
		}

		float GetEyeDepth() const;

		const PixelValues& GetRawValues() const;

		static RasterizedPixel AdditionalAlpha( int x, int y, PixelValues values, float alpha );
		const static RasterizedPixel discard;

	public:
		const bool isValid;
		const Vector2Int coordinate;

	private:
		const PixelValues values;
	};

}