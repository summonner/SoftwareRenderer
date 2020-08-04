#pragma once
#include "IRasterizer.h"
#include "Renderer/Vertex.h"

class Bounds;
namespace Renderer
{
	class PointRasterizer final : public IRasterizer
	{
	public:
		PointRasterizer( const Vertex& v );
		~PointRasterizer() override;

		float CheckFacet() const override;
		DerivativeTexcoord Derivative( const bool isTextureEnabled ) const override;
		void Rasterize( const Bounds& bounds, const ProcessPixel process ) override;

	private:
		Vertex v;
	};
}