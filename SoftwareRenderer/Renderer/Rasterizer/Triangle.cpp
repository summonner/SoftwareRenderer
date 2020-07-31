#include "framework.h"
#include "Triangle.h"
#include "Renderer/Vertex.h"
#include "Math/RangeInt.h"
#include "Math/Vector3.hpp"
#include "Math/Bounds.h"
#include "RasterizedPixel.h"
#include "Point.h"
#include "BresenhamList.h"
#include "PixelValues.h"

namespace Renderer
{
	Triangle::Triangle( const std::vector<Vertex>& vertices, const DerivativeTexcoord& derivatives )
		: vertices( vertices )
		, minmax { 0, 0 }
		, derivatives( derivatives )
	{
		assert( vertices.size() >= 3 );
		for ( auto i = 1; i < vertices.size(); ++i )
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
	}

	Triangle::~Triangle()
	{
	}

	void Triangle::Rasterize( const Bounds& bounds, ProcessPixel process )
	{
		if ( minmax.first == minmax.second )
		{
			return;
		}

		if ( derivatives.IsValid() == false )
		{
			Point( vertices[0] ).Rasterize( bounds, process );
			return;
		}

		std::vector<const Vertex*> v1, v2;
		v1.reserve( vertices.size() - 1 );
		v2.reserve( vertices.size() - 1 );
		for ( auto i = minmax.first; i != minmax.second; i = (i + 1) % vertices.size() )
		{
			v1.push_back( &vertices[i] );
		}
		v1.push_back( &vertices[minmax.second] );

		for ( auto i = minmax.first; i != minmax.second; i = (i > 0) ? (i - 1) : (vertices.size() - 1) )
		{
			v2.push_back( &vertices[i] );
		}
		v2.push_back( &vertices[minmax.second] );

		auto range = bounds.y.Clamp( vertices[minmax.first].screen.y, vertices[minmax.second].screen.y );
		Bounds adjust( bounds.x, range );
		BresenhamList e1( v1 );
		BresenhamList e2( v2 );
		Rasterize( adjust, e1, e2, process, derivatives );
	}

	void Triangle::Rasterize( const Bounds& bounds, BresenhamList& e1, BresenhamList& e2, ProcessPixel process, const DerivativeTexcoord& derivatives )
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

	bool Triangle::AscendingY( const Vertex& left, const Vertex& right )
	{
		return left.screen.y < right.screen.y;
	}
}