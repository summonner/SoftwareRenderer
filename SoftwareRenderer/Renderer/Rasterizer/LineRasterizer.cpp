#include "framework.h"
#include "LineRasterizer.h"
#include "Math/Bounds.h"
#include "Algorithm/Bresenham.h"
#include "RasterizedPixel.h"
#include "Renderer/Vertex.h"
#include "Renderer/Rasterizer/PointRasterizer.h"
#include "DerivativeTexcoord.h"
#include "Algorithm/XiaolinWu.h"
#include "Algorithm/BresenhamList.h"
#include "PolygonRasterizer.h"

namespace Renderer
{
	LineRasterizer::LineRasterizer( std::vector<Vertex>&& vertices, float width, bool smooth, ShadeModel::ShadeFunc shadeFunc )
		: vertices( std::move( vertices ) )
		, shadeFunc( shadeFunc )
		, width( std::min( width, 10.f ) )
		, smooth( smooth )
	{
		assert( this->vertices.size() == 2 );
	}

	LineRasterizer::LineRasterizer( const Vertex& a, const Vertex& b, ShadeModel::ShadeFunc shadeFunc )
		: vertices( { a, b } )
		, shadeFunc( shadeFunc )
		, width( 1.f )
		, smooth( false )
	{
	}

	LineRasterizer::~LineRasterizer()
	{
	}

	void LineRasterizer::Rasterize( const Bounds& bounds, PolygonMode::Mode mode, const ProcessPixel process )
	{
		if ( smooth )
		{
			if ( width <= 1.f )
			{
				SmoothThinLine( bounds, process );
			}
			else
			{
				SmoothWideLine( bounds, process );
			}
		}
		else
		{
			if ( width <= 1.f )
			{
				ThinLine( bounds, process );
			}
			else
			{
				WideLine( bounds, process );
			}
		}
	}

	float LineRasterizer::CheckFacet() const
	{
		return 0.f;
	}

	DerivativeTexcoord LineRasterizer::Derivative( const bool isTextureEnabled ) const
	{
		if ( isTextureEnabled == false )
		{
			return DerivativeTexcoord::invalid;
		}

		return DerivativeTexcoord::Line( vertices[0], vertices[1] );
	}

	void LineRasterizer::ThinLine( const Bounds& bounds, const ProcessPixel process ) const
	{
		auto e = Bresenham( vertices[0], vertices[1], shadeFunc );
		do
		{
			if ( bounds.Contains( e.p ) == false )
			{
				continue;
			}

			process( RasterizedPixel( e ) );
		} while ( e.Next() );
	}

	void LineRasterizer::WideLine( const Bounds& bounds, const ProcessPixel process ) const
	{
		auto e = Bresenham( vertices[0], vertices[1], shadeFunc );
		const auto half = width * 0.5f;
		const auto xmajor = e.IsXMajor();
		const auto bound = xmajor ? bounds : Bounds( bounds.y, bounds.x );
		do
		{
			if ( bound.x.Contains( e.p.x ) == false )
			{
				continue;
			}

			const auto p = xmajor ? e.p : Vector2Int( e.p.y, e.p.x );
			const auto values = e.GetValues();
			const auto range = bound.y.Clamp( (int)(p.y - half), (int)(p.y + half) );
			for ( auto y : range )
			{
				const auto p2 = xmajor ? Vector2Int( p.x, y ) : Vector2Int( y, p.x );
				process( RasterizedPixel( p2, values ) );
			}
		} while ( e.Next() );
	}

	void LineRasterizer::SmoothThinLine( const Bounds& bounds, const ProcessPixel process ) const
	{
		auto e = XiaolinWu( vertices[0], vertices[1], shadeFunc );
		const auto isXMajor = e.IsXMajor();
		const auto bound = isXMajor ? bounds : Bounds( bounds.y, bounds.x );
		do
		{
			const auto x = isXMajor ? (int)e.p.x : (int)e.p.y;
			if ( bound.x.Contains( x ) == false )
			{
				continue;
			}

			const auto values = e.GetValues();
			const auto y = isXMajor ? e.p.y : e.p.x;
			auto yi = (int)y;
			if ( bound.y.Contains( yi ) )
			{
				const auto frac = 1 - (y - yi);
				const auto p = isXMajor ? Vector2Int( x, yi ) : Vector2Int( yi, x );
				process( RasterizedPixel( p, AddAlpha( values, frac ) ) );
			}

			yi += 1;
			if ( bound.y.Contains( yi ) )
			{
				const auto frac = 1 - (yi - y);
				const auto p = isXMajor ? Vector2Int( x, yi ) : Vector2Int( yi, x );
				process( RasterizedPixel( p, AddAlpha( values, frac ) ) );
			}
		} while ( e.Next() );
	}

	void LineRasterizer::SmoothWideLine( const Bounds& bounds, const ProcessPixel process ) const
	{
		const auto diff = vertices[1].position - vertices[0].position;
		const auto n = Vector2( diff.y, -diff.x ).Normalize() * (width * 0.5f);
		
		std::vector<Vertex> offsets =
		{
			vertices[0].Offset( -n ),
			vertices[0].Offset( n ),
			vertices[1].Offset( n ),
			vertices[1].Offset( -n ),
		};

		auto square = PolygonRasterizer( std::move( offsets ), 1, 2, shadeFunc );
		square.Rasterize( bounds, Renderer::PolygonMode::Mode::Fill, process );
	}

	PixelValues LineRasterizer::AddAlpha( const PixelValues& values, float alpha )
	{
		auto color = values.color;
		color.w *= alpha;

		return PixelValues{
			values.w,
			values.depth,
			color,
			values.texcoord,
		};
	}
}