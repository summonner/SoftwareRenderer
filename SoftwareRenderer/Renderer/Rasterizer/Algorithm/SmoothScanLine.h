#pragma once
#include "../ShadeModel.h"
#include "../IRasterizer.h"
#include "ScanLine.h"

namespace Renderer
{
	class SmoothScanLine final : public Scanline
	{
	public:
		SmoothScanLine( const std::vector<Vertex>& vertices, const std::pair<size_t, size_t> minmax, ShadeModel::ShadeFunc shadeFunc );
		~SmoothScanLine();

	protected:
		RangeInt Next( int y );
		RasterizedPixel GetPixel( int x, int y, PixelValues&& values );

	private:
		std::pair<int, int> FillAlpha( int y );

	private:
		std::unordered_map<int, float> alpha;
	};
}