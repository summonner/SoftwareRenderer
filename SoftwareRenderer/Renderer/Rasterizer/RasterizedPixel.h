#pragma once
#include "Math/Vector2.hpp"
#include "Math/Vector4.hpp"

namespace Renderer
{
	class RasterizedPixel
	{
	public:
		RasterizedPixel( const Vector2Int& coordinate, const Vector4& color, float depth, const Vector2& texcoord );
		~RasterizedPixel();

		const static RasterizedPixel discard;
	private:
		RasterizedPixel();

	public:
		const Vector2Int coordinate;
		const bool isValid;
		const Vector4 color;
		const float depth;
		const Vector2 texcoord;
	};

}