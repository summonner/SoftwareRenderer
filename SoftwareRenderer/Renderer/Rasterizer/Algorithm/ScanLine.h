#pragma once
#include "../ShadeModel.h"
#include "BresenhamList.h"
#include "../IRasterizer.h"
#include "Math/RangeInt.h"

class RangeInt;
namespace Renderer
{
	class Vertex;
	class BresenhamList;
	using ProcessPixel = IRasterizer::ProcessPixel;
	class Scanline
	{
	public:
		static std::unique_ptr<Scanline> Create( const std::vector<Vertex>& vertices, ShadeModel::ShadeFunc shadeFunc, bool smooth );
		Scanline( const std::vector<Vertex>& vertices, const std::pair<size_t, size_t> minmax, ShadeModel::ShadeFunc shadeFunc, bool smooth );
		~Scanline();

		void Rasterize( const Bounds& bounds, const ProcessPixel process );

	protected:
		virtual RangeInt Next( int y );
		virtual RasterizedPixel GetPixel( int x, int y, PixelValues&& values );

	private:
		static std::pair<size_t, size_t> FindMinMax( const std::vector<Vertex>& vertices );
		static std::vector<const Vertex*> BuildEdge( const std::vector<Vertex>& vertices, const std::pair<size_t, size_t>& minmax, std::function<size_t( size_t, size_t )> Next );
		static size_t Forward( size_t i, size_t max );
		static size_t Backward( size_t i, size_t max );

		static bool AscendingY( const Vertex& left, const Vertex& right );

	protected:
		BresenhamList e1;
		BresenhamList e2;
		ShadeModel::ShadeFunc shadeFunc;

	public:
		const RangeInt rangeY;
	};
}