#include "framework.h"
#include "Line.h"
#include "Renderer/Vertex.h"
#include "Renderer/RasterizedPixel.h"
#include "Math/Vector4.hpp"
#include "Math/Vector2.hpp"

namespace Renderer
{
	Line::Line( const Vertex& a, const Vertex& b )
		: a( a )
		, b( b )
		, squaredThickness( 5.f * 5.f )
	{
	}

	Line::~Line()
	{
	}

	// realtime collision detection
	// http://www.r-5.org/files/books/computers/algo-list/realtime-3d/Christer_Ericson-Real-Time_Collision_Detection-EN.pdf
	Line::Result Line::RasterizeInternal( const Vector2& c ) const
	{
		auto a = this->a.screen;
		auto b = this->b.screen;

		auto ab = b - a;
		auto ac = c - a;
		auto t = ac.Dot( ab );
		if ( t < 0 )
		{
			return Result { 0, -1 };
		}

		auto denom = ab.Dot( ab );
		if ( denom == 0 )
		{
			return Result { 0, ac.Dot( ac ) };
		}

		if ( t > denom )
		{
			return Result { 1, -1 };
		}

		auto squaredDistance = ac.Dot( ac ) - t * t / (float)denom;
		return Result { t / (float)denom, squaredDistance };
	}

	RasterizedPixel Line::Rasterize( const Vector2& coordinate ) const
	{
		auto r = RasterizeInternal( coordinate );
		auto isDiscard = r.squaredDistance < 0
					  || r.squaredDistance > squaredThickness;
		if ( isDiscard == true )
		{
			return RasterizedPixel::discard;
		}
	
		return Lerp( Vector2( 1 - r.t, r.t ) );
	}

	RasterizedPixel Line::Lerp( const Vector2& barycentric ) const
	{
		auto color = a.color * barycentric.x + b.color * barycentric.y;
		Vector2 z( a.position.z, b.position.z );
		auto depth = barycentric.Dot( z );
		return RasterizedPixel( color, depth );
	}
}