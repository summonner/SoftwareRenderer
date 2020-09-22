#pragma once
#include "IRasterizer.h"
#include "ShadeModel.h"

class Bounds;
namespace Renderer
{
	class Vertex;
	struct PixelValues;
	class LineRasterizer final : public IRasterizer
	{
	public:
		LineRasterizer( std::vector<Vertex>&& vertices, float width, bool smooth, ShadeModel::ShadeFunc shadeFunc );
		LineRasterizer( const Vertex& a, const Vertex& b, ShadeModel::ShadeFunc shadeFunc );
		~LineRasterizer() override;

		float CheckFacet() const override;
		DerivativeTexcoord Derivative( const bool isTextureEnabled ) const override;
		void Rasterize( const Bounds& bounds, PolygonMode::Mode mode, const ProcessPixel process ) override;

	private:
		void ThinLine( const Bounds& bounds, const ProcessPixel process ) const;
		void WideLine( const Bounds& bounds, const ProcessPixel process ) const;
		void SmoothThinLine( const Bounds& bounds, const ProcessPixel process ) const;
		void SmoothWideLine( const Bounds& bounds, const ProcessPixel process ) const;

		static PixelValues AddAlpha( const PixelValues& source, float alpha );

	private:
		const std::vector<Vertex> vertices;
		const ShadeModel::ShadeFunc shadeFunc;
		const float width;
		const bool smooth;
	};
}