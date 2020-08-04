#pragma once
#include "CommonRasterizer.h"

class Bounds;
namespace Renderer
{
	class Vertex;
	class LineRasterizer final : public CommonRasterizer
	{
	public:
		LineRasterizer( std::vector<Vertex>&& vertices );
		~LineRasterizer() override;

		bool PostPerspectiveDivide() override;
		bool CheckFacet( const CullFunc cullFunc ) const override;
		DerivativeTexcoord Derivative( const bool isTextureEnabled ) const override;
		void Rasterize( const Bounds& bounds, const ProcessPixel process ) override;
	};
}