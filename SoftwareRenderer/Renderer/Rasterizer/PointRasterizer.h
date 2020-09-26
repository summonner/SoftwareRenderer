#pragma once
#include "IRasterizer.h"
#include "Renderer/Vertex.h"

class Bounds;
namespace Renderer
{
	struct PixelValues;
	class PointRasterizer final : public IRasterizer
	{
	public:
		PointRasterizer( const Vertex& v );
		PointRasterizer( const Vertex& v, float size, bool smooth );
		~PointRasterizer() override;

		float CheckFacet() const override;
		DerivativeTexcoord Derivative( const bool isTextureEnabled ) const override;
		void Rasterize( const Bounds& bounds, PolygonMode::Mode mode, const ProcessPixel process ) override;

		void Point( const ProcessPixel process ) const;
		void Square( const Bounds& bounds, const ProcessPixel process ) const;
		void Circle( const Bounds& bounds, const ProcessPixel process ) const;

	private:
		Vertex v;
		const float half;
		const bool smooth;
	};
}