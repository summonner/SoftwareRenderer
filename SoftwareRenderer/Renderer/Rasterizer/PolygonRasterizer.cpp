#include "framework.h"
#include "PolygonRasterizer.h"
#include "PointRasterizer.h"
#include "BresenhamList.h"
#include "RasterizedPixel.h"
#include "Renderer/Vertex.h"
#include "Math/Bounds.h"

namespace Renderer
{
	PolygonRasterizer::PolygonRasterizer( std::vector<Vertex>&& vertices, std::function<DerivativeTexcoord()> derivativeBuilder )
		: CommonRasterizer( std::move( vertices ), derivativeBuilder )
	{
		assert( this->vertices.size() > 0 );
	}

	PolygonRasterizer::~PolygonRasterizer()
	{
	}

	void PolygonRasterizer::Rasterize( const Bounds& bounds, ProcessPixel process, const DerivativeTexcoord& derivatives )
	{
		const auto minmax = FindMinMax();
		if ( minmax.first == minmax.second )
		{
			return;
		}

		auto range = bounds.y.Clamp( vertices[minmax.first].screen.y, vertices[minmax.second].screen.y );
		Bounds adjust( bounds.x, range );

		auto e1 = BuildEdge( minmax, &PolygonRasterizer::Forward );
		auto e2 = BuildEdge( minmax, &PolygonRasterizer::Backward );
		Rasterize( adjust, e1, e2, process, derivatives );
	}

	std::pair<size_t, size_t> PolygonRasterizer::FindMinMax() const
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

	BresenhamList PolygonRasterizer::BuildEdge( const std::pair<size_t, size_t>& minmax, std::function<size_t( const PolygonRasterizer&, size_t )> Next ) const
	{
		std::vector<const Vertex*> v;
		v.reserve( vertices.size() - 1 );
		for ( auto i = minmax.first; i != minmax.second; i = Next( *this, i ) )
		{
			v.push_back( &vertices[i] );
		}
		v.push_back( &vertices[minmax.second] );

		return BresenhamList( v );
	}

	size_t PolygonRasterizer::Forward( size_t i ) const
	{
		if ( i < vertices.size() - 1 )
		{
			return ++i;
		}
		else
		{
			return 0;
		}
	}

	size_t PolygonRasterizer::Backward( size_t i ) const
	{
		if ( i > 0 )
		{
			return --i;
		}
		else
		{
			return vertices.size() - 1;
		}
	}

	void PolygonRasterizer::Rasterize( const Bounds& bounds, BresenhamList& e1, BresenhamList& e2, ProcessPixel process, const DerivativeTexcoord& derivatives )
	{
		for ( const auto y : bounds.y )
		{
			e1.NextY( y );
			e2.NextY( y );

			const float length = (float)(e2.x - e1.x);
			if ( length == 0.f )
			{
				process( RasterizedPixel( e1.GetCurrent(), derivatives ) );
				continue;
			}

			const auto values1 = e1.GetValues();
			const auto values2 = e2.GetValues();

			const auto minmax = std::minmax( e1.x, e2.x );
			for ( const auto x : bounds.x.Clamp( minmax.first, minmax.second ) )
			{
				const auto t = (float)(x - e1.x) / length;
				const auto values = PixelValues::Lerp( values1, values2, t );
				process( RasterizedPixel( Vector2Int( x, y ), values, derivatives ) );
			}
		}
	}

	bool PolygonRasterizer::AscendingY( const Vertex& left, const Vertex& right )
	{
		return left.position.y < right.position.y;
	}
}