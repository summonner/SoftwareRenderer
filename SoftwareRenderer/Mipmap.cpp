#include "framework.h"
#include "Mipmap.h"
#include "Math/Vector4.hpp"
#include "Util/IImageSource.h"


namespace Renderer
{
	Mipmap::Mipmap( IImageSource* source )
		: width( source->width )
		, height( source->height )
		, size( source->width - 1.f, source->height - 1.f )
		, data( new Color4[source->width * source->height] )
	{
		for ( auto p : *source )
		{
			auto i = ToIndex( p.x, p.y );
			auto pixel = source->GetPixel( p );
			data[i] = pixel;
		}
	}

	Mipmap::~Mipmap()
	{
	}

	Vector4 Mipmap::GetPixel( int x, int y ) const
	{
		auto i = ToIndex( x, y );
		auto pixel = data[i];
		return Vector4( pixel.x, pixel.y, pixel.z, pixel.w ) / 255.f;
	}
}