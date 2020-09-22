#include "framework.h"
#include "PolygonRasterizer.h"
#include "LineRasterizer.h"
#include "PointRasterizer.h"
#include "Algorithm/BresenhamList.h"
#include "RasterizedPixel.h"
#include "DerivativeTexcoord.h"
#include "Renderer/Vertex.h"
#include "Math/Bounds.h"
#include "PolygonMode.h"

namespace Renderer
{
	const Dictionary<PolygonMode::Mode, PolygonRasterizer::PolygonModeFunc> PolygonRasterizer::polygonModeFunc( 
	{
		{ PolygonMode::Mode::Fill, &PolygonRasterizer::Fill },
		{ PolygonMode::Mode::Line, &PolygonRasterizer::Line },
		{ PolygonMode::Mode::Point, &PolygonRasterizer::Point },
	}, &PolygonRasterizer::Point );

	PolygonRasterizer::PolygonRasterizer( std::vector<Vertex>&& vertices, int secondIndex, int thirdIndex, ShadeModel::ShadeFunc shadeFunc )
		: vertices( std::move( vertices ) )
		, a( this->vertices[0] )
		, b( this->vertices[secondIndex] )
		, c( this->vertices[thirdIndex] )
		, shadeFunc( shadeFunc )
	{
		assert( this->vertices.size() >= 3 );
	}

	PolygonRasterizer::~PolygonRasterizer()
	{
	}

	float PolygonRasterizer::CheckFacet() const
	{
		const auto ab = b.screen - a.screen;
		const auto ac = c.screen - a.screen;
		return ab.Area( ac );
	}

	DerivativeTexcoord PolygonRasterizer::Derivative( bool isTextureEnabled ) const
	{
		if ( isTextureEnabled == false )
		{
			return DerivativeTexcoord::invalid;
		}

		return DerivativeTexcoord::Triangle( a, b, c );
	}

	void PolygonRasterizer::Rasterize( const Bounds& bounds, PolygonMode::Mode mode, const ProcessPixel process )
	{
		polygonModeFunc[mode]( this, bounds, process );
	}

	void PolygonRasterizer::Fill( const Bounds& bounds, const ProcessPixel process )
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
		Rasterize( adjust, e1, e2, process, shadeFunc );
	}

	void PolygonRasterizer::Line( const Bounds& bounds, const ProcessPixel process )
	{
		auto previous = vertices[vertices.size() - 1];
		for ( const auto& current : vertices )
		{
			LineRasterizer line( previous, current, shadeFunc );
			line.Rasterize( bounds, PolygonMode::Mode::Line, process );
			previous = current;
		}
	}

	void PolygonRasterizer::Point( const Bounds& bounds, const ProcessPixel process )
	{
		for ( const auto& v : vertices )
		{
			PointRasterizer point( v );
			point.Rasterize( bounds, PolygonMode::Mode::Point, process );
		}
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

		return BresenhamList( v, shadeFunc );
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

	void PolygonRasterizer::Rasterize( const Bounds& bounds, BresenhamList& e1, BresenhamList& e2, const ProcessPixel process, const ShadeModel::ShadeFunc shadeFunc )
	{
		for ( const auto y : bounds.y )
		{
			e1.NextY( y );
			e2.NextY( y );

			const float length = (float)(e2.x - e1.x);
			if ( length == 0.f )
			{
				continue;
			}

			const auto values1 = e1.GetValues();
			const auto values2 = e2.GetValues();
			const auto shading = (shadeFunc != nullptr) ? shadeFunc : ShadeModel::SmoothFunc( values1.color, values2.color );

			const auto minmax = std::minmax( e1.x, e2.x );
			for ( const auto x : bounds.x.Clamp( minmax.first, minmax.second ) )
			{
				const auto t = (float)(x - e1.x) / length;
				const PixelValues values {
					::Lerp( values1.w, values2.w, t ),
					::Lerp( values1.depth, values2.depth, t ),
					shading( t ),
					Vector2::Lerp( values1.texcoord, values2.texcoord, t )
				};
				process( RasterizedPixel( Vector2Int( x, y ), values ) );
			}
		}
	}

	bool PolygonRasterizer::AscendingY( const Vertex& left, const Vertex& right )
	{
		return left.position.y < right.position.y;
	}

	std::unique_ptr<IRasterizer> PolygonRasterizer::Create( std::vector<Vertex>&& vertices, const Vector4& flatColor )
	{
		const int secondIndex = SelectSecondVertex( vertices );
		if ( secondIndex < 0 )
		{
			return std::make_unique<PointRasterizer>( vertices[0] );
		}

		const auto shadeFunc = ShadeModel::FlatFunc( flatColor );
		const int thirdIndex = SelectThirdVertex( vertices, secondIndex );
		if ( thirdIndex < 0 )
		{
			return std::make_unique<LineRasterizer>( vertices[0], vertices[secondIndex], shadeFunc );
		}

		return std::unique_ptr<IRasterizer>( new PolygonRasterizer( std::move( vertices ), secondIndex, thirdIndex, shadeFunc ) );
	}

	int PolygonRasterizer::SelectSecondVertex( const std::vector<Vertex>& vertices )
	{
		for ( auto i = 0u; i < vertices.size(); ++i )
		{
			if ( vertices[i].screen != vertices[0].screen )
			{
				return (int)i;
			}
		}

		return -1;
	}

	int PolygonRasterizer::SelectThirdVertex( const std::vector<Vertex>& vertices, size_t secondIndex )
	{
		const auto ab = vertices[secondIndex].screen - vertices[0].screen;
		for ( auto i = secondIndex + 1; i < vertices.size(); ++i )
		{
			const auto ac = vertices[i].screen - vertices[0].screen;
			if ( ab.Area( ac ) != 0 )
			{
				return (int)i;
			}
		}

		return -1;
	}
}