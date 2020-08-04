#pragma once
#include "IRasterizer.h"

class Bounds;
namespace Renderer
{
	class Vertex;
	class LineRasterizer final : public IRasterizer
	{
	public:
		LineRasterizer( std::vector<Vertex>&& vertices );
		LineRasterizer( const Vertex& a, const Vertex& b );
		~LineRasterizer() override;

		bool CheckFacet( const CullFunc cullFunc ) const override;
		DerivativeTexcoord Derivative( const bool isTextureEnabled ) const override;
		void Rasterize( const Bounds& bounds, const ProcessPixel process ) override;

	private:
		const std::vector<Vertex> vertices;
	};
}