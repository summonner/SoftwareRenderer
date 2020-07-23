#include "framework.h"
#include "glTextureManager.h"
#include "Renderer/Texturing/Texture2D.h"
#include "Math/Vector4.hpp"

void glTextureManager::Generate( int num, GLuint* outHandles )
{
	GLuint i = 0u;
	while ( num > 0 && i < MAXUINT )
	{
		++i;
		if ( textures.find( i ) != textures.end() )
		{
			continue;
		}

		textures.emplace( i, nullptr );

		*outHandles = i;
		++outHandles;
		--num;
	}
}

void glTextureManager::Delete( GLuint handle )
{
	textures.erase( handle );
}

std::shared_ptr<ITexture> glTextureManager::Bind( GLuint handle )
{
	current = handle;
	return textures[current];
}

void glTextureManager::SetImage( GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels )
{
	auto source = new glImageSource( width, height, format, type, pixels );
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
		return Color4( pixels[i + 0],
						pixels[i + 1],
						pixels[i + 2],
						255 );
	default:
		assert( "Not implemented yet" && false );
		return Color4::zero;
	}
}