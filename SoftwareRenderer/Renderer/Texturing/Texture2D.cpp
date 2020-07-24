#include "framework.h"
#include "Texture2D.h"
#include "Util/IImageSource.h"
#include "Math/Vector4.hpp"
#include "Math/Vector2.hpp"
#include "Util/StlMapExtension.h"

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
		auto wrapped = wrapFuncs( uv );
		return FilterNearest( wrapped );
	}

	void Texture2D::SetWrapMode( ITexture::WrapMode uMode, ITexture::WrapMode vMode )
	{
		wrapFuncs.u = StlMapExtension::Find( wrapFuncTable, uMode, (Texture2D::WrapFunc)&Texture2D::WrapClamp );
		wrapFuncs.v = StlMapExtension::Find( wrapFuncTable, vMode, (Texture2D::WrapFunc)&Texture2D::WrapClamp );
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

	std::map<ITexture::WrapMode, Texture2D::WrapFunc> Texture2D::wrapFuncTable =
	{
		{ ITexture::WrapMode::Clamp, &Texture2D::WrapClamp },
		{ ITexture::WrapMode::Repeat, &Texture2D::WrapRepeat },
		{ ITexture::WrapMode::MirroredRepeat, &Texture2D::WrapMirror }
	};

	float Texture2D::WrapClamp( float v )
	{
		return std::clamp( v, 0.f, 1.f );
	}

	float Texture2D::WrapRepeat( float v )
	{
		return v - (int)v + (v >= 0.f ? 0 : 1);
	}

	float Texture2D::WrapMirror( float v )
	{
		v = std::fmodf( v, 2.f );
		if ( v < 0 )
		{
			v *= -1;
		}

		v = (v - 1);
		if ( v < 0 )
		{
			v *= -1;
		}
		return v;
	}

	Vector2 Texture2D::WrapFuncs::operator ()( const Vector2& uv ) const
	{
		return Vector2(
			u( uv.x ),
			v( uv.y )
		);
	}
}