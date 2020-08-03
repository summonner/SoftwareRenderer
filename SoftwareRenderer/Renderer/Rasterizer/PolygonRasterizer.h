#pragma once
#include "CommonRasterizer.h"
#include "DerivativeTexcoord.h"

namespace Renderer
{
	class Vertex;
	class BresenhamList;
	class PolygonRasterizer final : public CommonRasterizer
	{
	public:
		PolygonRasterizer( std::vector<Vertex>&& vertices );
		~PolygonRasterizer() override;

		void Rasterize( const Bounds& bounds, ProcessPixel process, const DerivativeTexcoord& derivatives ) override;

	private:
		std::pair<size_t, size_t> FindMinMax() const;
		BresenhamList BuildEdge( const std::pair<size_t, size_t>& minmax, std::function<size_t( const PolygonRasterizer&, size_t )> Next ) const;
		size_t Forward( size_t i ) const;
		size_t Backward( size_t i ) const;

		static bool AscendingY( const Vertex& left, const Vertex& right );
		static void Rasterize( const Bounds& bounds, BresenhamList& e1, BresenhamList& e2, ProcessPixel process, const DerivativeTexcoord& derivatives );
	};
}