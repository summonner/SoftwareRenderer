#include "framework.h"
#include "Texture2D.h"
#include "Util/IImageSource.h"
#include "Math/Vector4.hpp"
#include "Math/Vector2.hpp"

namespace Renderer
{
	Texture2D::Texture2D( IImageSource* image )
		: width( image->width )
		, size( image->width - 1, image->height - 1 )
		, texelSize( 1.f / image->width, 1.f / image->height )
		, data( new Color4[ image->width * image->height ] )
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

	Vector4 Texture2D::GetPixel( const Vector2& uv ) const
	{
		auto wrapped = wrapMode( uv );
		return FilterNearest( wrapped );
	}

	void Texture2D::SetWrapMode( WrapMode::Type uMode, WrapMode::Type vMode )
	{
		wrapMode.u = uMode;
		wrapMode.v = vMode;
	}

	Vector4 Texture2D::GetPixel( int x, int y ) const
	{
		auto i = ToIndex( x, y );
		auto pixel = data[i];
		return Vector4( pixel.x, pixel.y, pixel.z, pixel.w ) / 255.f;
	}

	Vector4 Texture2D::FilterNearest( const Vector2& uv ) const
	{
		auto p = uv * size;
		return GetPixel( (int)p.x, (int)p.y );
	}

	Vector4 Texture2D::FilterLinear( const Vector2& uv ) const
	{
		return Vector4::zero;
	}


	Vector2 Texture2D::WrapModes::operator ()( const Vector2& uv ) const
	{
		return Vector2(
			u( uv.x ),
			v( uv.y )
		);
	}
}