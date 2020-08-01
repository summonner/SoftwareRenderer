#pragma once
#include "IRasterizer.h"

class Bounds;
namespace Renderer
{
	class Vertex;
	class DerivativeTexcoord;
	class Line final : public IRasterizer
	{
	public:
		Line( const Vertex& a, const Vertex& b );
		~Line() override;

		void Rasterize( const Bounds& bounds, ProcessPixel process );

	private:
		DerivativeTexcoord Derivative() const;

	private:
		const Vertex& a;
		const Vertex& b;
	};
}