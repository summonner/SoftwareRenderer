#pragma once
#include "IRasterizer.h"
#include "DerivativeTexcoord.h"

namespace Renderer
{
	class Vertex;
	class BresenhamList;
	class Polygon final : public IRasterizer
	{
	public:
		Polygon( std::vector<Vertex>&& vertices, std::function<DerivativeTexcoord()> derivativeBuilder );
		~Polygon();

		void Rasterize( const Matrix4x4& viewport, const Bounds& bounds, ProcessPixel process ) override;

	private:
		std::pair<size_t, size_t> FindMinMax() const;
		BresenhamList BuildEdge( const std::pair<size_t, size_t>& minmax, std::function<size_t( const Polygon&, size_t )> Next ) const;
		size_t Forward( size_t i ) const;
		size_t Backward( size_t i ) const;

		static bool AscendingY( const Vertex& left, const Vertex& right );
		static void Rasterize( const Bounds& bounds, BresenhamList& e1, BresenhamList& e2, ProcessPixel process, const DerivativeTexcoord& derivatives );

	private:
		std::vector<Vertex> vertices;
		std::function<DerivativeTexcoord()> derivativeBuilder;
	};
}