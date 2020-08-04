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

		bool PerspectiveDivide( const Matrix4x4& viewport ) override;
		bool CheckFacet( const CullFunc cullFunc ) const override;
		DerivativeTexcoord Derivative( const bool isTextureEnabled ) const override;
		void Rasterize( const Bounds& bounds, const ProcessPixel process ) override;

	private:
		Vertex v;
	};
}