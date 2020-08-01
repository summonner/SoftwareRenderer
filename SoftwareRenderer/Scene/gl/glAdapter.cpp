#include "framework.h"
#include "glAdapter.h"
#include "glTextureManager.h"
#include "Renderer/IRenderer.h"

std::shared_ptr<IRenderer> _renderer;
glTextureManager textureManager;
#define renderer _renderer

WINGDIAPI void APIENTRY glEnable( GLenum cap )
{
	switch ( cap )
	{
	case GL_TEXTURE_2D:
		return;
	}
}

WINGDIAPI void APIENTRY glClear( GLbitfield mask )
{
	renderer->Clear();
}

WINGDIAPI void APIENTRY glLoadIdentity( void )
{
	renderer->LoadIdentity();
}

WINGDIAPI void APIENTRY glTranslatef( GLfloat x, GLfloat y, GLfloat z )
{
	renderer->Translate( x, y, z );
}

WINGDIAPI void APIENTRY glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z )
{
	renderer->Rotate( angle, x, y, z );
}

WINGDIAPI void APIENTRY glScalef( GLfloat x, GLfloat y, GLfloat z )
{
	renderer->Scale( x, y, z );
}

IRenderer::DrawMode Convert( GLenum mode )
{
	switch ( mode )
	{
	case GL_LINES:
		return IRenderer::DrawMode::Lines;
	case GL_LINE_STRIP:
		return IRenderer::DrawMode::LineStrip;
	case GL_LINE_LOOP:
		return IRenderer::DrawMode::LineLoop;
	case GL_TRIANGLES:
		return IRenderer::DrawMode::Triangles;
	case GL_QUADS:
		return IRenderer::DrawMode::Quads;
	case GL_POINTS:
	default:
		return IRenderer::DrawMode::Points;
	}
}

WINGDIAPI void APIENTRY glBegin( GLenum mode )
{
	auto drawMode = Convert( mode );
	renderer->Begin( drawMode );
}

WINGDIAPI void APIENTRY glColor3f( GLfloat red, GLfloat green, GLfloat blue )
{
	renderer->Color( red, green, blue );
}

WINGDIAPI void APIENTRY glVertex3f( GLfloat x, GLfloat y, GLfloat z )
{
	renderer->AddVertex( x, y, z );
}

WINGDIAPI void APIENTRY glTexCoord2f( GLfloat s, GLfloat t )
{
	renderer->TexCoord( s, t );
}

WINGDIAPI void APIENTRY glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz )
{
//	renderer->Normal( nx, ny, nz );
}

WINGDIAPI void APIENTRY glEnd( void )
{
	renderer->End();
}

WINGDIAPI void APIENTRY glGenTextures( GLsizei n, GLuint *textures )
{
	textureManager.Generate( n, textures );
}

WINGDIAPI void APIENTRY glBindTexture( GLenum target, GLuint texture )
{
	auto t = textureManager.Bind( texture );
	renderer->BindTexture( t );
}

WINGDIAPI void APIENTRY glTexImage2D( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels )
{
	textureManager.SetImage( level, internalformat, width, height, format, type, pixels );
}

WINGDIAPI void APIENTRY glTexParameteri( GLenum target, GLenum pname, GLint param )
{
	switch ( pname )
	{
	case GL_TEXTURE_WRAP_S:
		textureManager.SetWrapModeS( param );
		return;
	case GL_TEXTURE_WRAP_T:
		textureManager.SetWrapModeT( param );
		return;
	case GL_TEXTURE_MAG_FILTER:
		textureManager.SetMagFilter( param );
		return;
	case GL_TEXTURE_MIN_FILTER:
		textureManager.SetMinFilter( param );
		return;
	}
}

WINGDIAPI void APIENTRY glDeleteTextures( GLsizei n, const GLuint* textures )
{
	while ( n > 0 )
	{
		textureManager.Delete( *textures );
		++textures;
		--n;
	}
}

int APIENTRY gluBuild2DMipmaps(
	GLenum      target,
	GLint       components,
	GLint       width,
	GLint       height,
	GLenum      format,
	GLenum      type,
	const void* data )
{
	textureManager.SetImage( 0, components, width, height, format, type, data );
	return 1;
}