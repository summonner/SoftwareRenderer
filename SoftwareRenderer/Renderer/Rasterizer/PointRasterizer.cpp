#include "framework.h"
#include "PointRasterizer.h"
#include "Math/Bounds.h"
#include "RasterizedPixel.h"
#include "DerivativeTexcoord.h"
#include "Algorithm/ScanLine.h"
#include "Algorithm/BresenhamList.h"
#include "Algorithm/BresenhamCircle.h"

namespace Renderer
{
	PointRasterizer::PointRasterizer( const Vertex& v )
		: PointRasterizer( v, 1.f, false )
	{
	}

	PointRasterizer::PointRasterizer( const Vertex& v, float size, bool smooth )
		: v( v )
		, half( size * 0.5f )
		, smooth( smooth )
	{
	}

	PointRasterizer::~PointRasterizer()
	{
	}

	float PointRasterizer::CheckFacet() const
	{
		return 0.f;
	}
	
	DerivativeTexcoord PointRasterizer::Derivative( const bool isTextureEnabled ) const
	{
		return DerivativeTexcoord::invalid;
	}

	void PointRasterizer::Rasterize( const Bounds& bounds, PolygonMode::Mode mode, const ProcessPixel process )
	{
		if ( bounds.Contains( v.screen ) == false )
		{
			return;
		}

		if ( half <= 0.5f )
		{
			Point( process );
		}
		else if ( smooth == true )
		{
			Circle( bounds, process );
		}
		else
		{
			Square( bounds, process );
		}
	}

	void PointRasterizer::Point( const ProcessPixel process ) const
	{
		process( RasterizedPixel( v ) );
	}

	void PointRasterizer::Square( const Bounds& bounds, const ProcessPixel process ) const
	{
		std::vector<Vertex> offsets(
		{
			v.Offset( -half, -half ),
			v.Offset( half, -half ),
			v.Offset( half,  half ),
			v.Offset( -half,  half ),
		} );

		ShadeModel::ShadeFunc shadeFunc = ShadeModel::FlatFunc( v.color );
		auto scanline = Scanline::Create( offsets, shadeFunc, false );
		if ( scanline == nullptr )
		{
			return;
		}

		scanline->Rasterize( bounds, process );
	}

	void PointRasterizer::Circle( const Bounds& bounds, const ProcessPixel process ) const
	{
		PixelValues values
		{
			v.position.w,
			v.position.z,
			v.color,
			v.texcoord
		};

		BresenhamCircle e( v.screen, half );
		do
		{
			auto y = e.p.y + v.screen.y;
			if ( bounds.y.Contains( y ) == false )
			{
				continue;
			}

			auto range = bounds.x.Clamp( v.screen.x - e.p.x, v.screen.x + e.p.x );
			for ( auto x : range )
			{
				Vector2Int p( x, y );
				process( RasterizedPixel( p, values ) );
			}
		} while ( e.NextY() );
	}
}