#include "framework.h"
#include "Texture2D.h"
#include "Util/IImageSource.h"
#include "Math/Vector4.hpp"
#include "Math/Vector2.hpp"

namespace Renderer
{
	Texture2D::Texture2D( IImageSource* image )
		: width( image->width )
		, height( image->height )
		, data( new Color4[ width * height ] )
	{
		for ( auto p : *image )
		{
			auto i = ToIndex( p );
			auto pixel = image->GetPixel( p );
			data[i] = pixel;
		}
	}

	Texture2D::~Texture2D()
	{
	}

	Vector4 Texture2D::GetPixel( const Vector2& p ) const
	{
		auto x = (int)(p.x * (width - 1));
		auto y = (int)(p.y * (height - 1));
		auto i = ToIndex( x, y );

		auto pixel = data[i];

		return Vector4( pixel.x, pixel.y, pixel.z, pixel.w ) / 255.f;
	}
}