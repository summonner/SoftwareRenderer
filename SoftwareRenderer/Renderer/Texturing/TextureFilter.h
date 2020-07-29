#pragma once
#include "Math/Vector4.hpp"
#include "Util/Dictionary.hpp"

namespace Renderer
{
	class Mipmap;
	class TextureFilter final
	{
	public:
		using MipmapChain = std::vector<std::unique_ptr<Mipmap>>;
		enum class MinType
		{
			Nearest,
			Linear,
			NearestMipmapNearest,
			NearestMipmapLinear,
			LinearMipmapNearest,
			LinearMipmapLinear,
		};

		enum class MagType
		{
			Nearest,
			Linear
		};

		TextureFilter();
		~TextureFilter();

		Vector4 operator ()( const Vector2& p, const MipmapChain& mipmaps, float mipLevel ) const;
		void operator =( MinType type );
		void operator =( MagType type );

	private:
		using FilterFunc = std::function<Vector4( const Vector2& p, const Mipmap& mipmap )>;
		FilterFunc magFilter;

		struct MinFilter
		{
			Vector4 operator ()( const Vector2& uv, const MipmapChain& mipmaps, float mipLevel ) const;

			std::function<std::pair<int, float>( float )> mipmap;
			FilterFunc filter;
		} minFilter;

	public:
		static Vector4 Nearest( const Vector2& p, const Mipmap& mipmap );
		static Vector4 Linear( const Vector2& p, const Mipmap& mipmap );

	private:
		static std::pair<int, float> NoMipmap( float mipLevel );
		static std::pair<int, float> NearestMipmap( float mipLevel );
		static std::pair<int, float> LinearMipmap( float mipLevel );

		static const Dictionary<MagType, FilterFunc> magTable;
		static const Dictionary<MinType, MinFilter> minTable;
		static const MinFilter MinNearest;
	};
}

using TextureMagFilter = Renderer::TextureFilter::MagType;
using TextureMinFilter = Renderer::TextureFilter::MinType;