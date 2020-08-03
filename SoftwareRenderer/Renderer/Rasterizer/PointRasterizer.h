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

		void PerspectiveDivide( const Matrix4x4& viewport ) override;
		bool CheckFacet( CullFunc cullFunc ) override;
		void Rasterize( const Bounds& bounds, ProcessPixel process ) override;

	private:
		Vertex v;
	};
}