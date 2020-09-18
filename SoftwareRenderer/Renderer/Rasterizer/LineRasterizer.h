#pragma once
#include "IRasterizer.h"
#include "ShadeModel.h"

class Bounds;
namespace Renderer
{
	class Vertex;
	class LineRasterizer final : public IRasterizer
	{
	public:
		LineRasterizer( std::vector<Vertex>&& vertices, ShadeModel::ShadeFunc shadeFunc );
		LineRasterizer( const Vertex& a, const Vertex& b, ShadeModel::ShadeFunc shadeFunc );
		~LineRasterizer() override;

		float CheckFacet() const override;
		DerivativeTexcoord Derivative( const bool isTextureEnabled ) const override;
		void Rasterize( const Bounds& bounds, PolygonMode::Mode mode, const ProcessPixel process ) override;

	private:
		const std::vector<Vertex> vertices;
		const ShadeModel::ShadeFunc shadeFunc;
	};
}