#include "framework.h"
#include "glAdapter.h"
#include "glTextureManager.h"
#include "Renderer/IRenderer.h"
#include "Math/Vector4.hpp"

std::shared_ptr<IRenderer> _renderer;
glTextureManager textureManager;
#define renderer _renderer

void glEnable( GLenum cap, bool enable )
{
	switch ( cap )
	{
	case GL_DEPTH_TEST:
		renderer->depthBuffer.SetEnable( enable );
		break;

	case GL_TEXTURE_2D:
		renderer->texture.SetEnable( enable );
		break;

	case GL_BLEND:
		renderer->blender.SetEnable( enable );
		break;
	}
}

WINGDIAPI void APIENTRY glEnable( GLenum cap )
{
	glEnable( cap, true );
}

WINGDIAPI void APIENTRY glDisable( GLenum cap )
{
	glEnable( cap, false );
}

WINGDIAPI void APIENTRY glClear( GLbitfield mask )
{
	if ( mask & GL_COLOR_BUFFER_BIT )
	{
		renderer->Clear();
	}

	if ( mask & GL_DEPTH_BUFFER_BIT )
	{
		renderer->depthBuffer.Clear();
	}
}

WINGDIAPI void APIENTRY glClearColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha )
{
	renderer->SetClearColor( red, green, blue, alpha );
}

WINGDIAPI void APIENTRY glClearDepth( GLclampd depth )
{
	renderer->depthBuffer.SetClearValue( (float)depth );
}

WINGDIAPI void APIENTRY glDepthFunc( GLenum func )
{
	static const Dictionary<GLenum, DepthFunc> table
	{
		{ GL_NEVER, DepthFunc::Never },
		{ GL_LESS, DepthFunc::Less },
		{ GL_EQUAL, DepthFunc::Equal },
		{ GL_LEQUAL, DepthFunc::LEqual },
		{ GL_GREATER, DepthFunc::Greater },
		{ GL_NOTEQUAL, DepthFunc::NotEqual },
		{ GL_GEQUAL, DepthFunc::GEqual },
		{ GL_ALWAYS, DepthFunc::Always },
	};

	renderer->depthBuffer.SetDepthFunc( table[func] );
}

WINGDIAPI void APIENTRY glViewport( GLint x, GLint y, GLsizei width, GLsizei height )
{
	renderer->Viewport( x, y, width, height );
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

WINGDIAPI void APIENTRY glBegin( GLenum mode )
{
	static const Dictionary<GLenum, IRenderer::DrawMode> table
	{
		{ GL_POINTS, IRenderer::DrawMode::Points },
		{ GL_LINES, IRenderer::DrawMode::Lines },
		{ GL_LINE_STRIP, IRenderer::DrawMode::LineStrip },
		{ GL_LINE_LOOP, IRenderer::DrawMode::LineLoop },
		{ GL_TRIANGLES, IRenderer::DrawMode::Triangles },
		{ GL_TRIANGLE_STRIP, IRenderer::DrawMode::TriangleFan },
		{ GL_TRIANGLE_FAN, IRenderer::DrawMode::TriangleFan },
		{ GL_QUADS, IRenderer::DrawMode::Quads },
	};

	renderer->Begin( table[mode] );
}

WINGDIAPI void APIENTRY glColor3f( GLfloat red, GLfloat green, GLfloat blue )
{
	renderer->Color( red, green, blue, 1.f );
}

WINGDIAPI void APIENTRY glColor4f( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
	renderer->Color( red, green, blue, alpha );
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
	renderer->texture.Bind( t );
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

WINGDIAPI void APIENTRY glBlendFunc( GLenum sfactor, GLenum dfactor )
{
	static const Dictionary<GLenum, BlendFunc> table
	{
		{ GL_ZERO, BlendFunc::Zero },
		{ GL_ONE, BlendFunc::One },
		{ GL_SRC_COLOR, BlendFunc::SrcColor },
		{ GL_ONE_MINUS_SRC_COLOR, BlendFunc::OneMinusSrcColor },
		{ GL_DST_COLOR, BlendFunc::DstColor },
		{ GL_ONE_MINUS_DST_COLOR, BlendFunc::OneMinusDstColor },
		{ GL_SRC_ALPHA, BlendFunc::SrcAlpha },
		{ GL_ONE_MINUS_SRC_ALPHA, BlendFunc::OneMinusSrcAlpha },
		{ GL_DST_ALPHA, BlendFunc::DstAlpha },
		{ GL_ONE_MINUS_DST_ALPHA, BlendFunc::OneMinusDstAlpha },
		{ GL_SRC_ALPHA_SATURATE, BlendFunc::SrcAlphaSaturate },
	};
	renderer->blender.SetBlendFunc( table[sfactor], table[dfactor] );
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

void APIENTRY gluPerspective(
	GLdouble fovy,
	GLdouble aspect,
	GLdouble zNear,
	GLdouble zFar )
{
	renderer->Perspective( (float)fovy, (float)aspect, (float)zNear, (float)zFar );
}