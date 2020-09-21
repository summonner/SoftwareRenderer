#pragma once
#include "IRasterizer.h"
#include "ShadeModel.h"

namespace Renderer
{
	class Vertex;
	class BresenhamList;
	class PolygonRasterizer final : public IRasterizer
	{
	private:
		PolygonRasterizer( std::vector<Vertex>&& vertices, int secondIndex, int thirdIndex, ShadeModel::ShadeFunc shadeFunc );
	public:
		static std::unique_ptr<IRasterizer> Create( std::vector<Vertex>&& vertices, const Vector4& flatColor );
		~PolygonRasterizer() override;

		void Rasterize( const Bounds& bounds, PolygonMode::Mode mode, const ProcessPixel process ) override;
		float CheckFacet() const override;
		DerivativeTexcoord Derivative( const bool isTextureEnabled ) const override;

		static void Rasterize( const Bounds& bounds, BresenhamList& e1, BresenhamList& e2, const ProcessPixel process, const ShadeModel::ShadeFunc shadeFunc );
	private:
		std::pair<size_t, size_t> FindMinMax() const;
		BresenhamList BuildEdge( const std::pair<size_t, size_t>& minmax, std::function<size_t( const PolygonRasterizer&, size_t )> Next ) const;
		size_t Forward( size_t i ) const;
		size_t Backward( size_t i ) const;

		static bool AscendingY( const Vertex& left, const Vertex& right );

		static int SelectSecondVertex( const std::vector<Vertex>& vertices );
		static int SelectThirdVertex( const std::vector<Vertex>& vertices, size_t secondIndex );

	private:
		const ShadeModel::ShadeFunc shadeFunc;
		const std::vector<Vertex> vertices;
		const Vertex& a;
		const Vertex& b;
		const Vertex& c;

	private:
		void Fill( const Bounds& bounds, const ProcessPixel process );
		void Line( const Bounds& bounds, const ProcessPixel process );
		void Point( const Bounds& bounds, const ProcessPixel process );
		using PolygonModeFunc = std::function<void( PolygonRasterizer*, const Bounds& bounds, const ProcessPixel process )>;
		static const Dictionary<PolygonMode::Mode, PolygonModeFunc> polygonModeFunc;
	};
}