#include "framework.h"
#include "Texture2D.h"
#include "Util/IImageSource.h"
#include "Math/Vector4.hpp"
#include "Math/Vector2.hpp"

namespace Renderer
{
	Texture2D::Texture2D( IImageSource* image )
		: width( image->width )
		, size( image->width - 1.f, image->height - 1.f )
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
		return FilterLinear( wrapped );
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
		auto p = uv * size + 0.5f;
		return GetPixel( (int)p.x, (int)p.y );
	}

	Vector4 Texture2D::FilterLinear( const Vector2& uv ) const
	{
		Vector2Int p( uv * size );
		Vector2 t = uv * size - p;
		if ( t.x <= 0.f )
		{
			if ( t.y <= 0.f )
			{
				return GetPixel( p.x, p.y );
			}
			else if ( t.y >= 1.f )
			{
				return GetPixel( p.x, p.y + 1 );
			}
			else
			{
				auto p00 = GetPixel( p.x, p.y );
				auto p01 = GetPixel( p.x, p.y + 1 );
				return Vector4::Lerp( p00, p01, t.y );
			}
		}
		else if ( t.x >= 1.f )
		{
			if ( t.y <= 0.f )
			{
				return GetPixel( p.x + 1, p.y );
			}
			else if ( t.y >= 1.f )
			{
				return GetPixel( p.x + 1, p.y + 1 );
			}
			else
			{
				auto p10 = GetPixel( p.x + 1, p.y );
				auto p11 = GetPixel( p.x + 1, p.y + 1 );
				return Vector4::Lerp( p10, p11, t.y );
			}
		}
		else
		{
			if ( t.y <= 0.f )
			{
				auto p00 = GetPixel( p.x, p.y );
				auto p10 = GetPixel( p.x + 1, p.y );
				return Vector4::Lerp( p00, p10, t.x );
			}
			else if ( t.y >= 1.f )
			{
				auto p01 = GetPixel( p.x + 1, p.y );
				auto p11 = GetPixel( p.x + 1, p.y + 1 );
				return Vector4::Lerp( p01, p11, t.x );
			}
			else
			{
				auto p00 = GetPixel( p.x, p.y );
				auto p10 = GetPixel( p.x + 1, p.y );
				auto p01 = GetPixel( p.x, p.y + 1 );
				auto p11 = GetPixel( p.x + 1, p.y + 1 );

				return p00 * (1 - t.x) * (1 - t.y)
					+ p10 * t.x * (1 - t.y)
					+ p01 * (1 - t.x) * t.y
					+ p11 * t.x * t.y;
			}
		}
	}


	Vector2 Texture2D::WrapModes::operator ()( const Vector2& uv ) const
	{
		return Vector2(
			u( uv.x ),
			v( uv.y )
		);
	}
}