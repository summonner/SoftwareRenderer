#include "framework.h"
#include "Mipmap.h"
#include "Math/Vector4.hpp"
#include "Util/IImageSource.h"
#include "TextureFilter.h"

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
		: IImageSource( (source.width + 1) / 2, (source.height + 1) / 2 )
		, size( width - 1.f, height - 1.f )
		, data( new Color4[width * height] )
	{
		for ( auto p : *this )
		{
			const auto i = ToIndex( p.x, p.y );
			auto q = (Vector2( p ) * 2 + 0.5) / source.size;
			q.x = std::min( q.x, 1.f );
			q.y = std::min( q.y, 1.f );
			const auto color = TextureFilter::Linear( q, source );
			data[i] = Color4( BYTE(color.x * 255)
							, BYTE(color.y * 255)
							, BYTE(color.z * 255)
							, BYTE(color.w * 255) );
		}
	}

	Mipmap::~Mipmap()
	{
	}

	Dictionary<int, Vector4> colors( {
		{ 225, { 1, 1, 1, 1 } },
		{ 113, { 1, 0, 0, 1 } },
		{  57, { 0, 1, 0, 1 } },
		{  29, { 0, 0, 1, 1 } },
		{  15, { 1, 0, 0, 1 } },
		{   8, { 0, 1, 0, 1 } },
		{   4, { 0, 0, 1, 1 } },
		{   2, { 1, 0, 0, 1 } },
		{   1, { 0, 1, 0, 1 } },
	}, Vector4( 0.2f, 0.2f, 0.2f, 1 ) );

	Vector4 Mipmap::GetPixel( int x, int y ) const
	{
//		return colors[width];
		const auto i = ToIndex( x, y );
		const auto pixel = data[i];
		return Vector4( pixel.x, pixel.y, pixel.z, pixel.w ) / 255.f;
	}

	Color4 Mipmap::GetPixel( const Vector2Int& p ) const
	{
		const auto i = ToIndex( p.x, p.y );
		return data[i];
	}

	void Mipmap::SetPixel( const Vector2Int& p, const Vector4& value )
	{
		const auto i = ToIndex( p.x, p.y );
		data[i] = Color4( (BYTE)(value.x * 255.f),
						  (BYTE)(value.y * 255.f),
						  (BYTE)(value.z * 255.f),
						  (BYTE)(value.w * 255.f) );
	}
}