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
#include "Algorithm/VertexInterpolator.h"
#include "Algorithm/ScanLine.h"

namespace Renderer
{
	const Dictionary<PolygonMode::Mode, PolygonRasterizer::PolygonModeFunc> PolygonRasterizer::polygonModeFunc( 
	{
		{ PolygonMode::Mode::Fill, &PolygonRasterizer::Fill },
		{ PolygonMode::Mode::Line, &PolygonRasterizer::Line },
		{ PolygonMode::Mode::Point, &PolygonRasterizer::Point },
	}, &PolygonRasterizer::Point );

	PolygonRasterizer::PolygonRasterizer( std::vector<Vertex>&& vertices, int secondIndex, int thirdIndex, ShadeModel::ShadeFunc shadeFunc, bool smooth )
		: vertices( std::move( vertices ) )
		, a( this->vertices[0] )
		, b( this->vertices[secondIndex] )
		, c( this->vertices[thirdIndex] )
		, shadeFunc( shadeFunc )
		, smooth( smooth )
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
		auto scanline = Scanline::Create( vertices, shadeFunc, smooth );
		if ( scanline == nullptr )
		{
			return;
		}

		scanline->Rasterize( bounds, process );
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

		return std::unique_ptr<IRasterizer>( new PolygonRasterizer( std::move( vertices ), secondIndex, thirdIndex, shadeFunc, false ) );
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