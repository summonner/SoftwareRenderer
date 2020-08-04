#pragma once
#include "IRasterizer.h"

namespace Renderer
{
	class Vertex;
	class BresenhamList;
	class PolygonRasterizer final : public IRasterizer
	{
	public:
		PolygonRasterizer( std::vector<Vertex>&& vertices, const int secondIndex, const int thirdIndex );
		~PolygonRasterizer() override;

		void Rasterize( const Bounds& bounds, const ProcessPixel process ) override;
		bool CheckFacet( const CullFunc cullFunc ) const override;
		DerivativeTexcoord Derivative( const bool isTextureEnabled ) const override;

	private:
		std::pair<size_t, size_t> FindMinMax() const;
		BresenhamList BuildEdge( const std::pair<size_t, size_t>& minmax, std::function<size_t( const PolygonRasterizer&, size_t )> Next ) const;
		size_t Forward( size_t i ) const;
		size_t Backward( size_t i ) const;

		static bool AscendingY( const Vertex& left, const Vertex& right );
		static void Rasterize( const Bounds& bounds, BresenhamList& e1, BresenhamList& e2, const ProcessPixel process );

	private:
		const std::vector<Vertex> vertices;
		const Vertex& a;
		const Vertex& b;
		const Vertex& c;
	};
}