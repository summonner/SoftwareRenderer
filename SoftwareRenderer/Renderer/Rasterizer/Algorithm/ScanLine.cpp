#include "framework.h"
#include "ScanLine.h"
#include "Renderer/Vertex.h"
#include "Math/Bounds.h"
#include "../RasterizedPixel.h"
#include "SmoothScanLine.h"

namespace Renderer
{
	std::unique_ptr<Scanline> Scanline::Create( const std::vector<Vertex>& vertices, const ShadeModel::ShadeFunc shadeFunc, bool smooth )
	{
		auto minmax = FindMinMax( vertices );
		if ( minmax.first == minmax.second )
		{
			return nullptr;
		}

		if ( smooth )
		{
			return std::make_unique<SmoothScanLine>( vertices, minmax, shadeFunc );
		}
		else
		{
			return std::make_unique<Scanline>( vertices, minmax, shadeFunc, false );
		}
	}

	Scanline::Scanline( const std::vector<Vertex>& vertices, const std::pair<size_t, size_t> minmax, ShadeModel::ShadeFunc shadeFunc, bool smooth )
		: e1( BuildEdge( vertices, minmax, Forward ), shadeFunc, smooth )
		, e2( BuildEdge( vertices, minmax, Backward ), shadeFunc, smooth )
		, shadeFunc( shadeFunc )
		, rangeY( vertices[minmax.first].screen.y, vertices[minmax.second].screen.y )
	{
	}

	Scanline::~Scanline()
	{
	}

	std::pair<size_t, size_t> Scanline::FindMinMax( const std::vector<Vertex>& vertices )
	{
		std::pair<size_t, size_t> minmax( 0, 0 );

		for ( auto i = 1u; i < vertices.size(); ++i )
		{
			if ( AscendingY( vertices[i], vertices[minmax.first] ) == true )
			{
				minmax.first = i;
			}
			else if ( AscendingY( vertices[minmax.second], vertices[i] ) == true )
			{
				minmax.second = i;
			}
		}

		return minmax;
	}

	std::vector<const Vertex*> Scanline::BuildEdge( const std::vector<Vertex>& vertices, const std::pair<size_t, size_t>& minmax, std::function<size_t( size_t, size_t )> Next )
	{
		std::vector<const Vertex*> v;
		v.reserve( vertices.size() - 1 );
		for ( auto i = minmax.first; i != minmax.second; i = Next( i, vertices.size() ) )
		{
			v.push_back( &vertices[i] );
		}
		v.push_back( &vertices[minmax.second] );

		return v;
	}

	size_t Scanline::Forward( size_t i, size_t max )
	{
		if ( i < max - 1 )
		{
			return ++i;
		}
		else
		{
			return 0;
		}
	}

	size_t Scanline::Backward( size_t i, size_t max )
	{
		if ( i > 0 )
		{
			return --i;
		}
		else
		{
			return max - 1;
		}
	}

	bool Scanline::AscendingY( const Vertex& left, const Vertex& right )
	{
		return left.position.y < right.position.y;
	}

	void Scanline::Rasterize( const Bounds& bounds, const ProcessPixel process )
	{
		for ( auto y : bounds.y.Clamp( rangeY ) )
		{
			auto range = Next( y );

			const float length = (float)(range.Length() - 1);
			if ( length == 0.f )
			{
				continue;
			}

			const auto values = GetValues();
			for ( const auto x : bounds.x.Clamp( range ) )
			{
				const auto t = (float)(x - range.min) / length;
				const auto p = GetPixel( x, y, values.Get( t ) );
				process( p );
			}
		}
	}

	RangeInt Scanline::Next( int y )
	{
		e1.NextY( y );
		e2.NextY( y );

		auto x = std::minmax( e1.x, e2.x );
		return RangeInt( x.first, x.second );
	}

	RasterizedPixel Scanline::GetPixel( int x, int y, PixelValues&& values )
	{
		return RasterizedPixel( Vector2Int( x, y ), values );
	}

	VertexInterpolator Scanline::GetValues() const
	{
		if ( e1.x <= e2.x )
		{
			return VertexInterpolator( e1.GetValues(), e2.GetValues(), shadeFunc );
		}
		else
		{
			return VertexInterpolator( e2.GetValues(), e1.GetValues(), shadeFunc );
		}
	}
}