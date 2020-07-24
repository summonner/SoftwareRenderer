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
		void SetWrapMode( WrapMode u, WrapMode v );

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
		const Vector2 texelSize;
		const std::unique_ptr<Color4[]> data;

		using WrapFunc = std::function<float( float )>;
		struct WrapFuncs
		{
			WrapFunc u = &WrapClamp;
			WrapFunc v = &WrapClamp;

			Vector2 operator ()( const Vector2& uv ) const;
		} wrapFuncs;

	private:
		Vector4 GetPixel( int x, int y ) const;
		Vector4 FilterNearest( const Vector2& p ) const;
		Vector4 FilterLinear( const Vector2& p ) const;

		static float WrapClamp( float v );
		static float WrapRepeat( float v );
		static float WrapMirror( float v );
		static std::map<WrapMode, WrapFunc> wrapFuncTable;
	};
}