#pragma once
#include "Math/Vector4.hpp"

namespace Renderer
{
	class RasterizedPixel
	{
	public:
		RasterizedPixel( const Vector4& color, float depth );
		~RasterizedPixel();

		const static RasterizedPixel discard;
	private:
		RasterizedPixel();

	public:
		const bool isValid;
		const Vector4 color;
		const float depth;
	};

}