#pragma once
#include "Math/Vector2.hpp"

class IImageSource;
namespace Renderer
{
	class Mipmap final
	{
	public:
		Mipmap( IImageSource* source );
		~Mipmap();

		Vector4 GetPixel( int x, int y ) const;

	private:
		inline int ToIndex( int x, int y ) const
		{
			return y * width + x;
		}

	public:
		const int width;
		const int height;
		const Vector2 size;

	private:
		const std::unique_ptr<Color4[]> data;
	};

}