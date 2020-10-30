#include "framework.h"
#include "glTextureManager.h"
#include "Renderer/Texturing/Texture2D.h"
#include "Math/Vector4.hpp"

glTextureManager::glTextureManager()
	: current( 0 )
{
	textures.Add( 0, std::make_shared<Texture2D>() );
}

glTextureManager::~glTextureManager()
{
}

void glTextureManager::Generate( int num, GLuint* outHandles )
{
	GLuint i = 0u;
	while ( num > 0 && i < MAXUINT )
	{
		++i;
		if ( textures.Contains( i ) == true )
		{
			continue;
		}

		textures.Add( i, std::make_shared<Texture2D>() );

		*outHandles = i;
		++outHandles;
		--num;
	}
}

void glTextureManager::Delete( GLuint handle )
{
	if ( handle == 0 )
	{
		return;
	}

	textures.Remove( handle );
}

std::shared_ptr<ITexture> glTextureManager::Bind( GLuint handle )
{
	current = handle;
	return textures[current];
}

std::shared_ptr<ITexture> glTextureManager::SetImage( GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels )
{
	if ( auto texture = Get2D(); texture != nullptr )
	{
		glImageSource source( width, height, format, type, pixels, scale );
		texture->SetImage( source, level < 0 );
	}

	return textures[current];
}

std::shared_ptr<ITexture> glTextureManager::SetSubImage( GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels )
{
	if ( auto texture = Get2D(); texture != nullptr )
	{
		glImageSource source( width, height, format, type, pixels, scale );
		const Vector2Int offset( xoffset, yoffset );

		for ( auto x = 0; x < width; ++x )
		for ( auto y = 0; y < height; ++y )
		{
			const Vector2Int sourcePos( x, y );
			const auto p = sourcePos + offset;
			const auto pixel = source.GetPixel( sourcePos );
			texture->SetPixel( p, level, Vector4( pixel.x / 255.f, pixel.y / 255.f, pixel.z / 255.f, pixel.w / 255.f ) );
		}
	}

	return textures[current];
}

const Dictionary<GLint, TextureWrapMode> glTextureManager::wrapModeTable
{
	{ GL_CLAMP,  TextureWrapMode::Clamp },
	{ GL_REPEAT, TextureWrapMode::Repeat },
};

void glTextureManager::SetWrapModeS( GLint param )
{
	if ( auto texture = Get2D(); texture != nullptr )
	{
		texture->SetWrapMode( wrapModeTable[param], TextureWrapMode::_ );
	}
}

void glTextureManager::SetWrapModeT( GLint param )
{
	if ( auto texture = Get2D(); texture != nullptr )
	{
		texture->SetWrapMode( TextureWrapMode::_, wrapModeTable[param] );
	}
}

void glTextureManager::SetMinFilter( GLint param )
{
	static const Dictionary<GLint, TextureMinFilter> table
	{
		{ GL_NEAREST, TextureMinFilter::Nearest },
		{ GL_LINEAR, TextureMinFilter::Linear },
		{ GL_NEAREST_MIPMAP_NEAREST, TextureMinFilter::NearestMipmapNearest },
		{ GL_NEAREST_MIPMAP_LINEAR, TextureMinFilter::NearestMipmapLinear },
		{ GL_LINEAR_MIPMAP_NEAREST, TextureMinFilter::LinearMipmapNearest },
		{ GL_LINEAR_MIPMAP_LINEAR, TextureMinFilter::LinearMipmapLinear },
	};

	if ( auto texture = Get2D(); texture != nullptr )
	{
		texture->SetFilter( table[param] );
	}
}

void glTextureManager::SetMagFilter( GLint param )
{
	static const Dictionary<GLint, TextureMagFilter> table
	{
		{ GL_NEAREST, TextureMagFilter::Nearest },
		{ GL_LINEAR, TextureMagFilter::Linear },
	};

	if ( auto texture = Get2D(); texture != nullptr )
	{
		texture->SetFilter( table[param] );
	}
}

void glTextureManager::SetPixel( const Vector2Int& p, int mipLevel, const Vector4& value )
{
	if ( auto texture = Get2D(); texture != nullptr )
	{
		texture->SetPixel( p, mipLevel, value * scale );
	}
}

std::shared_ptr<Texture2D> glTextureManager::Get2D() const
{
	if ( current < 0 )
	{
		return nullptr;
	}

	return std::dynamic_pointer_cast<Texture2D>( textures[current] );
}

const Dictionary<GLenum, int> glTextureManager::formatTable
{
	{ GL_RGB, 3 },
	{ GL_RGBA, 4 },
};

glTextureManager::glImageSource::glImageSource( GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels, const Vector4& scale )
	: IImageSource( width, height )
	, pixels( (BYTE*)pixels )
	, format( format )
	, pixelSize( formatTable[format] )
	, scale( scale )
{
}

Color4 glTextureManager::glImageSource::GetPixel( const Vector2Int& p ) const 
{
	auto i = (p.y * width + p.x) * pixelSize;

	switch ( format )
	{
	case GL_RGB:
		return Color4(  (BYTE)(pixels[i + 0] * scale.x),
						(BYTE)(pixels[i + 1] * scale.y),
						(BYTE)(pixels[i + 2] * scale.z),
						255 );
	case GL_RGBA:
		return Color4(  (BYTE)(pixels[i + 0] * scale.x),
						(BYTE)(pixels[i + 1] * scale.y),
						(BYTE)(pixels[i + 2] * scale.z),
						(BYTE)(pixels[i + 3] * scale.w) );

	default:
		assert( "Not implemented yet" && false );
		return Color4::zero;
	}
}