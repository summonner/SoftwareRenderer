#include "framework.h"
#include "Polygon.h"
#include "Point.h"
#include "BresenhamList.h"
#include "RasterizedPixel.h"
#include "Renderer/Vertex.h"
#include "Math/Bounds.h"

namespace Renderer
{
	Polygon::Polygon( std::vector<Vertex>&& vertices, std::function<DerivativeTexcoord()> derivativeBuilder )
		: vertices( std::move( vertices ) )
		, derivativeBuilder( derivativeBuilder )
	{
		assert( this->vertices.size() > 0 );
	}

	Polygon::~Polygon()
	{
	}

	void Polygon::Rasterize( const Matrix4x4& viewport, const Bounds& bounds, ProcessPixel process )
	{
		auto derivatives = derivativeBuilder();
		if ( derivatives.IsValid() == false )
		{
			Point( vertices[0] ).Rasterize( bounds, process );
			return;
		}

		for ( auto& v : vertices )
		{
			v.PerspectiveDivide( viewport );
		}

		const auto minmax = FindMinMax();
		if ( minmax.first == minmax.second )
		{
			return;
		}

		auto range = bounds.y.Clamp( vertices[minmax.first].screen.y, vertices[minmax.second].screen.y );
		Bounds adjust( bounds.x, range );

		auto e1 = BuildEdge( minmax, &Polygon::Forward );
		auto e2 = BuildEdge( minmax, &Polygon::Backward );
		Rasterize( adjust, e1, e2, process, derivatives );
	}

	std::pair<size_t, size_t> Polygon::FindMinMax() const
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

	BresenhamList Polygon::BuildEdge( const std::pair<size_t, size_t>& minmax, std::function<size_t( const Polygon&, size_t )> Next ) const
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

	size_t Polygon::Forward( size_t i ) const
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

	size_t Polygon::Backward( size_t i ) const
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

	void Polygon::Rasterize( const Bounds& bounds, BresenhamList& e1, BresenhamList& e2, ProcessPixel process, const DerivativeTexcoord& derivatives )
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

	bool Polygon::AscendingY( const Vertex& left, const Vertex& right )
	{
		return left.position.y < right.position.y;
	}
}