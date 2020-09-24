#include "framework.h"
#include "SmoothScanLine.h"
#include "BresenhamList.h"
#include "VertexInterpolator.h"
#include "../RasterizedPixel.h"
#include "Math/Bounds.h"

namespace Renderer
{
	SmoothScanLine::SmoothScanLine( const std::vector<Vertex>& vertices, const std::pair<size_t, size_t> minmax, ShadeModel::ShadeFunc shadeFunc )
		: Scanline( vertices, minmax, shadeFunc, true )
	{
	}

	SmoothScanLine::~SmoothScanLine()
	{
	}

	std::pair<int, int> SmoothScanLine::FillAlpha( int y )
	{
		e1.NextY( y );
		e2.NextY( y );
		auto minmax = std::minmax( e1.x, e2.x );
		for ( auto x = minmax.first; x <= minmax.second; ++x )
		{
			alpha[x >> 1] += 0.25f;
		}

		return minmax;
	}

	RangeInt SmoothScanLine::Next( int y )
	{
		alpha.clear();
		auto x1 = FillAlpha( y * 2 );
		auto x2 = FillAlpha( y * 2 + 1 );

		auto start = std::min( x1.first, x2.first ) >> 1;
		auto end = (std::max( x1.second, x2.second ) + 1) >> 1;

		return RangeInt( start, end + 1 );
	}

	RasterizedPixel SmoothScanLine::GetPixel( int x, int y, PixelValues&& values )
	{
		values.color.w *= alpha[x];
		return Scanline::GetPixel( x, y, std::move( values ) );
	}
}