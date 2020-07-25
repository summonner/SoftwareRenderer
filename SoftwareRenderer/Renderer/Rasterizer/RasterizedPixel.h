#pragma once
#include "Math/Vector2.hpp"
#include "Math/Vector4.hpp"

namespace Renderer
{
	class Bresenham;
	class RasterizedPixel
	{
	public:
		RasterizedPixel( const Vector2Int& coordinate, float w, const Vector4& color, float depth, const Vector2& texcoord );
		RasterizedPixel( const Bresenham& edge );
		~RasterizedPixel();

		Vector4 GetColor() const;
		Vector2 GetTexcoord() const;

		const static RasterizedPixel discard;
	private:
		RasterizedPixel();

	public:
		const bool isValid;
		const Vector2Int coordinate;
		const float depth;

	private:
		const float w;
		const Vector4 color;
		const Vector2 texcoord;
	};

}