#include "framework.h"
#include "TextureFilter.h"
#include "Mipmap.h"

namespace Renderer
{
	TextureFilter::TextureFilter()
		: minFilter( MinNearest )
		, magFilter( Nearest )
	{
	}

	TextureFilter::~TextureFilter()
	{
	}

	Vector4 TextureFilter::operator ()( const Vector2& p, const MipmapChain& mipmaps, float mipLevel ) const
	{
		if ( mipLevel <= 0 )
		{
			return magFilter( p, *mipmaps[0] );
		}
		else
		{
			return minFilter( p, mipmaps, mipLevel );
		}
	}

	void TextureFilter::operator =( MinType type )
	{
		minFilter = minTable[type];
	}

	void TextureFilter::operator =( MagType type )
	{
		magFilter = magTable[type];
	}

	const Dictionary<TextureFilter::MagType, TextureFilter::FilterFunc> TextureFilter::magTable(
	{
		{ MagType::Nearest, Nearest },
		{ MagType::Linear, Linear }
	}, Nearest );

	const TextureFilter::MinFilter TextureFilter::MinNearest{ NoMipmap, Nearest };
	const Dictionary<TextureFilter::MinType, TextureFilter::MinFilter> TextureFilter::minTable(
	{
		{ MinType::Nearest, MinNearest },
		{ MinType::Linear, { NoMipmap, Linear } },
		{ MinType::NearestMipmapNearest, { NearestMipmap, Nearest } },
		{ MinType::NearestMipmapLinear, { NearestMipmap, Linear } },
		{ MinType::LinearMipmapNearest, { LinearMipmap, Nearest } },
		{ MinType::LinearMipmapLinear, { LinearMipmap, Linear } }
	}, MinNearest );

	Vector4 TextureFilter::Nearest( const Vector2& uv, const Mipmap& mipmap )
	{
		Vector2Int p = uv * mipmap.size + 0.5f;
		return mipmap.GetPixel( p.x, p.y );
	}

	Vector4 TextureFilter::Linear( const Vector2& uv, const Mipmap& mipmap )
	{
		const Vector2Int p( uv * mipmap.size );
		const Vector2 t = uv * mipmap.size - p;
		if ( t.x <= 0.f )
		{
			if ( t.y <= 0.f )
			{
				return mipmap.GetPixel( p.x, p.y );
			}
			else
			{
				const auto p00 = mipmap.GetPixel( p.x, p.y );
				const auto p01 = mipmap.GetPixel( p.x, p.y + 1 );
				return Vector4::Lerp( p00, p01, t.y );
			}
		}
		else
		{
			if ( t.y <= 0.f )
			{
				const auto p00 = mipmap.GetPixel( p.x, p.y );
				const auto p10 = mipmap.GetPixel( p.x + 1, p.y );
				return Vector4::Lerp( p00, p10, t.x );
			}
			else
			{
				const auto p00 = mipmap.GetPixel( p.x, p.y );
				const auto p10 = mipmap.GetPixel( p.x + 1, p.y );
				const auto p01 = mipmap.GetPixel( p.x, p.y + 1 );
				const auto p11 = mipmap.GetPixel( p.x + 1, p.y + 1 );

				return p00 * (1 - t.x) * (1 - t.y)
					+ p10 * t.x * (1 - t.y)
					+ p01 * (1 - t.x) * t.y
					+ p11 * t.x * t.y;
			}
		}
	}

	Vector4 TextureFilter::MinFilter::operator ()( const Vector2& uv, const MipmapChain& mipmaps, float mipLevel ) const
	{
		mipLevel = std::clamp( mipLevel, 0.f, (float)(mipmaps.size() - 1) );
		const auto select = mipmap( mipLevel );
		if ( select.second <= 0.f )
		{
			return filter( uv, *mipmaps[select.first] );
		}
		else
		{
			const auto color1 = filter( uv, *mipmaps[select.first] );
			const auto color2 = filter( uv, *mipmaps[select.first + 1] );
			return Vector4::Lerp( color1, color2, select.second );
		}
	}

	std::pair<int, float> TextureFilter::NoMipmap( float mipLevel )
	{
		return { 0, 0.f };
	}

	std::pair<int, float> TextureFilter::NearestMipmap( float mipLevel )
	{
		return { (int)(mipLevel + 0.5f), 0.f };
	}

	std::pair<int, float> TextureFilter::LinearMipmap( float mipLevel )
	{
		const auto select = (int)mipLevel;
		const auto t = mipLevel - select;
		return { select, t };
	}
}