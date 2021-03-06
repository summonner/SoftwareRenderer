#include "framework.h"
#include "Texture2D.h"
#include "Util/IImageSource.h"
#include "Math/Vector4.hpp"
#include "Math/Vector2.hpp"
#include "Mipmap.h"

namespace Renderer
{
	Texture2D::Texture2D()
		: size( 0, 0 )
	{
	}

	Texture2D::Texture2D( const IImageSource& source )
		: Texture2D( source, false )
	{
	}

	Texture2D::Texture2D( const IImageSource& source, const bool buildMipmap )
		: size( (float)source.width, (float)source.height )
	{
		SetImage( source, buildMipmap );
	}

	void Texture2D::SetImage( const IImageSource& source, const bool buildMipmap )
	{
		size.x = (float)source.width;
		size.y = (float)source.height;

		if ( buildMipmap == false )
		{
			mipmaps.reserve( 1 );
			mipmaps.emplace_back( std::make_unique<Mipmap>( source ) );
			return;
		}

		auto length = std::max( source.width, source.height );
		mipmaps.reserve( (int)std::ceil( std::log2( length ) ) );
		mipmaps.emplace_back( std::make_unique<Mipmap>( source ) );

		while ( length >>= 1 )
		{
			mipmaps.emplace_back( std::make_unique<Mipmap>( *mipmaps[mipmaps.size() - 1] ) );
		}
	}

	Texture2D::~Texture2D()
	{
	}

	float Texture2D::CalculateMipLevel( Vector2 ddx, Vector2 ddy ) const
	{
		ddx *= size;
		ddy *= size;
		const auto maxDelta = std::max( ddx.Dot( ddx ), ddy.Dot( ddy ) );
		if ( isnan( maxDelta ) )
		{
			return 0.f;
		}
		return std::log2f( maxDelta ) * 0.5f;
	}

	bool Texture2D::IsValid() const
	{
		return mipmaps.size() > 0
			&& size.x > 0
			&& size.y > 0;
	}

	Vector4 Texture2D::GetPixel( const Vector2& uv, float mipLevel ) const
	{
		const auto wrapped = wrapMode( uv );
		return filter( wrapped, mipmaps, mipLevel );
	}

	void Texture2D::SetPixel( const Vector2Int& p, int mipLevel, const Vector4& value )
	{
		mipLevel = std::clamp( mipLevel, 0, (int)mipmaps.size() - 1 );
		mipmaps[mipLevel]->SetPixel( p, value );
	}

	void Texture2D::SetFilter( TextureFilter::MinType type )
	{
		filter = type;
	}

	void Texture2D::SetFilter( TextureFilter::MagType type )
	{
		filter = type;
	}

	void Texture2D::SetWrapMode( WrapMode::Type uMode, WrapMode::Type vMode )
	{
		wrapMode.u = uMode;
		wrapMode.v = vMode;
	}

	Vector2 Texture2D::GetSize() const
	{
		return size;
	}

	Vector2 Texture2D::WrapModes::operator ()( const Vector2& uv ) const
	{
		return Vector2(
			u( uv.x ),
			v( uv.y )
		);
	}
}