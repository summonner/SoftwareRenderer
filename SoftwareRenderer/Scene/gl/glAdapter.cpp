#include "framework.h"
#include "glAdapter.h"
#include "Math/Vector4.hpp"
#include "glBridge.h"

glBridge* adapter;
#define renderer adapter->renderer
#define textureManager adapter->textureManager
#define lightManager adapter->lightManager
#define meshBuilder adapter->meshBuilder

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

	case GL_CULL_FACE:
		renderer->cullFace.SetEnable( enable );
		break;

	case GL_LIGHTING:
		renderer->lighting.SetEnable( enable );
		break;

	case GL_LIGHT0:
		if ( enable == true )
		{
			renderer->lighting.Add( lightManager.Get( cap ) );
		}
		else
		{
			renderer->lighting.Remove( lightManager.Get( cap ) );
		}
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

WINGDIAPI void APIENTRY glMatrixMode( GLenum mode )
{
	// TODO
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
	meshBuilder.Begin( mode );
}

WINGDIAPI void APIENTRY glColor3f( GLfloat red, GLfloat green, GLfloat blue )
{
	meshBuilder.Color( red, green, blue, 1.f );
}

WINGDIAPI void APIENTRY glColor4f( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
	meshBuilder.Color( red, green, blue, alpha );
}

WINGDIAPI void APIENTRY glVertex3f( GLfloat x, GLfloat y, GLfloat z )
{
	meshBuilder.Vertex( x, y, z );
}

WINGDIAPI void APIENTRY glTexCoord2f( GLfloat s, GLfloat t )
{
	meshBuilder.Texcoord( s, t );
}

WINGDIAPI void APIENTRY glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz )
{
	meshBuilder.Normal( nx, ny, nz );
}

WINGDIAPI void APIENTRY glEnd( void )
{
	const auto mesh = meshBuilder.End();
	renderer->Draw( mesh );
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
	auto t = textureManager.SetImage( level, internalformat, width, height, format, type, pixels );
	renderer->texture.Bind( t );
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

WINGDIAPI void APIENTRY glCullFace( GLenum mode )
{
	static const Dictionary<GLenum, CullFace> table
	{
		{ GL_BACK, CullFace::Back },
		{ GL_FRONT, CullFace::Front },
		{ GL_FRONT_AND_BACK, CullFace::FrontAndBack },
	};
	renderer->cullFace.SetCullFace( table[mode] );
}

WINGDIAPI void APIENTRY glFrontFace( GLenum mode )
{
	static const Dictionary<GLenum, FrontFace> table
	{
		{ GL_CW, FrontFace::CW },
		{ GL_CCW, FrontFace::CCW },
	};
	renderer->cullFace.SetFrontFace( table[mode] );
}

WINGDIAPI void APIENTRY glShadeModel( GLenum mode )
{
	// TODO
}

WINGDIAPI void APIENTRY glHint( GLenum target, GLenum mode )
{
	// Not Implement
}

WINGDIAPI void APIENTRY glLightfv( GLenum light, GLenum pname, const GLfloat *params )
{
	lightManager.Set( light, pname, params );
}


WINGDIAPI void APIENTRY glVertexPointer( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer )
{
	meshBuilder.Vertex( size, type, stride, pointer );
}

WINGDIAPI void APIENTRY glTexCoordPointer( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer ) 
{
	meshBuilder.Texcoord( size, type, stride, pointer );
}

WINGDIAPI void APIENTRY glColorPointer( GLint size, GLenum type, GLsizei stride, const GLvoid* pointer )
{
	meshBuilder.Color( size, type, stride, pointer );
}

WINGDIAPI void APIENTRY glNormalPointer( GLenum type, GLsizei stride, const GLvoid* pointer )
{
	meshBuilder.Normal( type, stride, pointer );
}

WINGDIAPI void APIENTRY glDrawArrays( GLenum mode, GLint first, GLsizei count )
{
	const auto mesh = meshBuilder.Build( mode, first, count );
	renderer->Draw( mesh );
}

WINGDIAPI void APIENTRY glDrawElements( GLenum mode, GLsizei count, GLenum type, const GLvoid* indices )
{
	const auto mesh = meshBuilder.Build( mode, count, type, indices );
	renderer->Draw( mesh );
}

WINGDIAPI void APIENTRY glEnableClientState( GLenum array )
{

}

WINGDIAPI void APIENTRY glDisableClientState( GLenum array ) 
{

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

GLUquadric* APIENTRY gluNewQuadric( void )
{
	return nullptr;
}

void APIENTRY gluDeleteQuadric(
	GLUquadric* state )
{
}

void APIENTRY gluQuadricNormals(
	GLUquadric* quadObject,
	GLenum              normals )
{
}

void APIENTRY gluQuadricTexture(
	GLUquadric* quadObject,
	GLboolean           textureCoords )
{
}

void APIENTRY gluQuadricOrientation(
	GLUquadric* quadObject,
	GLenum              orientation )
{
}

void APIENTRY gluQuadricDrawStyle(
	GLUquadric* quadObject,
	GLenum              drawStyle )
{
}

void APIENTRY gluCylinder(
	GLUquadric* qobj,
	GLdouble            baseRadius,
	GLdouble            topRadius,
	GLdouble            height,
	GLint               slices,
	GLint               stacks )
{
}

void APIENTRY gluDisk(
	GLUquadric* qobj,
	GLdouble            innerRadius,
	GLdouble            outerRadius,
	GLint               slices,
	GLint               loops )
{
}

void APIENTRY gluPartialDisk(
	GLUquadric* qobj,
	GLdouble            innerRadius,
	GLdouble            outerRadius,
	GLint               slices,
	GLint               loops,
	GLdouble            startAngle,
	GLdouble            sweepAngle )
{
}

void APIENTRY gluSphere(
	GLUquadric* qobj,
	GLdouble            radius,
	GLint               slices,
	GLint               stacks )
{
}