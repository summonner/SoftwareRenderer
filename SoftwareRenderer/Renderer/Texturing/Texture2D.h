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
		Texture2D();
		Texture2D( const IImageSource& source );
		Texture2D( const IImageSource& source, const bool buildMipmap );
		~Texture2D();

		void SetImage( const IImageSource& source, const bool buildMipmap );
		float CalculateMipLevel( Vector2 ddx, Vector2 ddy ) const override;
		Vector4 GetPixel( const Vector2& uv, float mipLevel ) const override;
		void SetPixel( const Vector2Int& p, int mipLevel, const Vector4& value );
		void SetWrapMode( WrapMode::Type u, WrapMode::Type v );
		void SetFilter( TextureFilter::MinType type );
		void SetFilter( TextureFilter::MagType type );
		Vector2 GetSize() const;

	private:
		Vector2 size;

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