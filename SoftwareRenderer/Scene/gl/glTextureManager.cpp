#include "framework.h"
#include "glTextureManager.h"
#include "Renderer/Texturing/Texture2D.h"
#include "Math/Vector4.hpp"

glTextureManager::glTextureManager()
	: current( 0 )
{
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

		textures.Add( i, nullptr );

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
	if ( handle == 0 )
	{
		return nullptr;
	}

	current = handle;
	return textures[current];
}

void glTextureManager::SetImage( GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels )
{
	if ( current == 0 )
	{
		return;
	}

	glImageSource source( width, height, format, type, pixels );
	textures[current].reset( new Renderer::Texture2D( source ) );
}


glTextureManager::glImageSource::glImageSource( GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels )
	: IImageSource( width, height )
	, pixels( (BYTE*)pixels )
	, format( format )
	, pixelSize( 3 )
{
}

Color4 glTextureManager::glImageSource::GetPixel( const Vector2Int& p ) const 
{
	auto i = (p.y * width + p.x) * pixelSize;

	switch ( format )
	{
	case GL_RGB:
		return Color4(  pixels[i + 0],
						pixels[i + 1],
						pixels[i + 2],
						255 );
	default:
		assert( "Not implemented yet" && false );
		return Color4::zero;
	}
}