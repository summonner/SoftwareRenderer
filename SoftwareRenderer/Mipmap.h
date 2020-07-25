#pragma once
#include "Math/Vector2.hpp"
#include "Util/IImageSource.h"

namespace Renderer
{
	class Mipmap final : private IImageSource
	{
	public:
		Mipmap( const Mipmap& source );
		Mipmap( const IImageSource& source );
		~Mipmap();

		Vector4 GetPixel( int x, int y ) const;

	private:
		Color4 GetPixel( const Vector2Int& p ) const override;

	private:
		inline int ToIndex( int x, int y ) const
		{
			return y * width + x;
		}

	public:
		const Vector2 size;

	private:
		const std::unique_ptr<Color4[]> data;
	};

}