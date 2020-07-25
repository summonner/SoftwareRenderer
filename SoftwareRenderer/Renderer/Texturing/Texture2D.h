#pragma once
#include "ITexture.h"
#include "Math/Vector2.hpp"
#include "WrapMode.h"
#include "TextureFilter.h"

class IImageSource;
namespace Renderer
{
	class Mipmap;
	class Texture2D final : public ITexture
	{
	public:
		Texture2D( IImageSource* data );
		~Texture2D();

		Vector4 GetPixel( const Vector2& uv ) const;
		void SetWrapMode( WrapMode::Type u, WrapMode::Type v );
		void SetFilter( TextureFilter::MinType type );
		void SetFilter( TextureFilter::MagType type );

	private:
		struct WrapModes
		{
			WrapMode u;
			WrapMode v;

			Vector2 operator ()( const Vector2& uv ) const;
		} wrapMode;

		TextureFilter filter;
		std::vector<std::unique_ptr<Mipmap>> mipmaps;
	};
}