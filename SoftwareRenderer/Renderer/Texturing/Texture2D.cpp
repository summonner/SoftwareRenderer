#include "framework.h"
#include "Texture2D.h"
#include "Util/IImageSource.h"
#include "Math/Vector4.hpp"
#include "Math/Vector2.hpp"
#include "Mipmap.h"

namespace Renderer
{
	Texture2D::Texture2D( IImageSource* image )
	{
		mipmaps.reserve( 1 );
		mipmaps.emplace_back( std::make_unique<Mipmap>( image ) );
	}

	Texture2D::~Texture2D()
	{
	}

	Vector4 Texture2D::GetPixel( const Vector2& uv ) const
	{
		const auto wrapped = wrapMode( uv );
		return filter( wrapped, mipmaps, 0 );
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

	Vector2 Texture2D::WrapModes::operator ()( const Vector2& uv ) const
	{
		return Vector2(
			u( uv.x ),
			v( uv.y )
		);
	}
}