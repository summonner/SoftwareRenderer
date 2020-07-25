#pragma once
#include "ITexture.h"
#include "Math/Vector2.hpp"
#include "WrapMode.h"

class IImageSource;
namespace Renderer
{
	class Texture2D final : public ITexture
	{
	public:
		Texture2D( IImageSource* data );
		~Texture2D();

		Vector4 GetPixel( const Vector2& uv ) const override;
		void SetWrapMode( WrapMode::Type u, WrapMode::Type v );

	private:
		inline int ToIndex( const Vector2Int& p ) const
		{
			return ToIndex( p.x, p.y );
		}

		inline int ToIndex( int x, int y ) const
		{
			return y * width + x;
		}

	private:
		const int width;
		const Vector2 size;
		const std::unique_ptr<Color4[]> data;

	private:
		Vector4 GetPixel( int x, int y ) const;
		Vector4 FilterNearest( const Vector2& p ) const;
		Vector4 FilterLinear( const Vector2& p ) const;

		struct WrapModes
		{
			WrapMode u;
			WrapMode v;

			Vector2 operator ()( const Vector2& uv ) const;
		} wrapMode;
	};
}