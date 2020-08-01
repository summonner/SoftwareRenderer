#pragma once
#include "IRasterizer.h"

namespace Renderer
{
	class Vertex;
	class DerivativeTexcoord;
	class CommonRasterizer abstract : public IRasterizer
	{
	public:
		CommonRasterizer( std::vector<Vertex>&& vertices, std::function<DerivativeTexcoord( void )> derivativeBuilder );
		virtual ~CommonRasterizer() override;

		void Rasterize( const Matrix4x4& viewport, const Bounds& bounds, ProcessPixel process ) override;
		virtual void Rasterize( const Bounds& bounds, ProcessPixel process, const DerivativeTexcoord& derivatives ) abstract;

	protected:
		std::vector<Vertex> vertices;

	private:
		std::function<DerivativeTexcoord( void )> derivativeBuilder;

	};
}