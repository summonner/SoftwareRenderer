#pragma once
#include "ITexture.h"
#include "Math/Vector2.hpp"

class IImageSource;
namespace Renderer
{
	class Texture2D final : public ITexture
	{
	public:
		Texture2D( IImageSource* data );
		~Texture2D();

		Vector4 GetPixel( const Vector2& uv ) const override;

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
		int width;
		int height;

		std::unique_ptr<Color4[]> data;
	};
}