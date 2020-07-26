#include "framework.h"
#include "Mipmap.h"
#include "Math/Vector4.hpp"
#include "Util/IImageSource.h"

namespace Renderer
{
	Mipmap::Mipmap( const IImageSource& source )
		: IImageSource( source.width, source.height )
		, size( source.width - 1.f, source.height - 1.f )
		, data( new Color4[source.width * source.height] )
	{
		for ( const auto p : source )
		{
			const auto i = ToIndex( p.x, p.y );
			const auto pixel = source.GetPixel( p );
			data[i] = pixel;
		}
	}

	Mipmap::Mipmap( const Mipmap& source )
		: IImageSource( std::max( source.width / 2, 1 ), std::max( source.height / 2, 1 ) )
		, size( width - 1.f, height - 1.f )
		, data( new Color4[width * height] )
	{
		for ( auto p : *this )
		{
			const auto i = ToIndex( p.x, p.y );
			p *= 2;
			const auto p00 = source.GetPixel( p );
			const auto p10 = source.GetPixel( p + Vector2Int::right );
			const auto p01 = source.GetPixel( p + Vector2Int::up );
			const auto p11 = source.GetPixel( p + Vector2Int::one );

			data[i] = Color4(
				(BYTE)(p00.x * 0.25f + p10.x * 0.25f + p01.x * 0.25f + p11.x * 0.25f),
				(BYTE)(p00.y * 0.25f + p10.y * 0.25f + p01.y * 0.25f + p11.y * 0.25f),
				(BYTE)(p00.z * 0.25f + p10.z * 0.25f + p01.z * 0.25f + p11.z * 0.25f),
				(BYTE)(p00.w * 0.25f + p10.w * 0.25f + p01.w * 0.25f + p11.w * 0.25f)
			);
		}
	}

	Mipmap::~Mipmap()
	{
	}

	Vector4 Mipmap::GetPixel( int x, int y ) const
	{
		const auto i = ToIndex( x, y );
		const auto pixel = data[i];
		return Vector4( pixel.x, pixel.y, pixel.z, pixel.w ) / 255.f;
	}

	Color4 Mipmap::GetPixel( const Vector2Int& p ) const
	{
		const auto i = ToIndex( p.x, p.y );
		return data[i];
	}
}