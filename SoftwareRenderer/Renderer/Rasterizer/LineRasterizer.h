#pragma once
#include "CommonRasterizer.h"

class Bounds;
namespace Renderer
{
	class Vertex;
	class DerivativeTexcoord;
	class LineRasterizer final : public CommonRasterizer
	{
	public:
		LineRasterizer( std::vector<Vertex>&& vertices, std::function<DerivativeTexcoord(void)> derivativeBuilder );
		~LineRasterizer() override;

		void Rasterize( const Bounds& bounds, ProcessPixel process, const DerivativeTexcoord& derivatives ) override;
	};
}