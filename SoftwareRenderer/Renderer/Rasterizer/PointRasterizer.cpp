#include "framework.h"
#include "PointRasterizer.h"
#include "Math/Bounds.h"
#include "RasterizedPixel.h"
#include "DerivativeTexcoord.h"
#include "Algorithm/ScanLine.h"
#include "Algorithm/BresenhamList.h"
#include "Algorithm/XiaolinWuCircle.h"
#include "Algorithm/PixelPair.h"

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
		const PixelValues values
		{
			v.position.w,
			v.position.z,
			v.color,
			v.texcoord
		};

		XiaolinWuCircle e( half );
		auto oldY = (int)(v.position.y - half);
		RangeInt x = bounds.x;
		do
		{
			const auto y = v.position.y + e.p.y;
			const auto yi = (int)y;

			if ( oldY < yi )
			{
				for ( auto xi : x )
				{
					process( RasterizedPixel( xi, oldY, values ) );
				}
				x = bounds.x;
			}

			if ( bounds.y.Contains( yi ) == false )
			{
				x = RangeInt( 0, 0 );
				oldY = yi;
				continue;
			}

			const auto pixels = e.Get( Vector2( v.position ) );
			pixels.first.Plot( bounds, process, values );

			if ( e.p.x > 0.5f )
			{
				pixels.second.Plot( bounds, process, values );
				x = x.Clamp( pixels.first.coord.x + 1, pixels.second.coord.x );
			}
			else
			{
				x = RangeInt( 0, 0 );
			}

			oldY = yi;
		} while ( e.Next() );
	}

	IRasterizer::Range PointRasterizer::Selection() const
	{
		return { v.position.z, v.position.z };
	}
}