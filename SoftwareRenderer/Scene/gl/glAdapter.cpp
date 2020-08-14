#include "framework.h"
#include "glAdapter.h"
#include "Math/Vector4.hpp"
#include "glBridge.h"
#include "GLUquadric.h"
#include "Renderer/Rasterizer/ShadeModel.h"

glBridge* adapter;
#define renderer adapter->renderer
#define textureManager adapter->textureManager
#define lightManager adapter->lightManager
#define meshBuilder adapter->meshBuilder
#define matrix adapter->matrix
#define texcoordGenerator adapter->texcoordGenerator

void glEnable( GLenum cap, bool enable )
{
	switch ( cap )
	{
	case GL_DEPTH_TEST:
		renderer->GetDepthBuffer().SetEnable( enable );
		break;

	case GL_STENCIL:
		renderer->GetStencilBuffer().SetEnable( enable );
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
	case GL_LIGHT1:
	case GL_LIGHT2:
	case GL_LIGHT3:
	case GL_LIGHT4:
	case GL_LIGHT5:
	case GL_LIGHT6:
	case GL_LIGHT7:
		if ( enable == true )
		{
			renderer->lighting.Add( lightManager.Get( cap ) );
		}
		else
		{
			renderer->lighting.Remove( lightManager.Get( cap ) );
		}
		break;

	case GL_TEXTURE_GEN_S:
	case GL_TEXTURE_GEN_T:
		{
			const auto i = cap - GL_TEXTURE_GEN_S;
			renderer->texture.texGen[i].SetEnable( enable );
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
		renderer->GetFrameBuffer().Clear();
	}

	if ( mask & GL_DEPTH_BUFFER_BIT )
	{
		renderer->GetDepthBuffer().Clear();
	}

	if ( mask & GL_STENCIL_BUFFER_BIT )
	{
		renderer->GetStencilBuffer().Clear();
	}
}

WINGDIAPI void APIENTRY glClearColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha )
{
	renderer->GetFrameBuffer().SetClearValue( Vector4( red, green, blue, alpha ) );
}

WINGDIAPI void APIENTRY glColorMask( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha )
{
	renderer->GetFrameBuffer().SetColorMask( red, green, blue, alpha );
}

WINGDIAPI void APIENTRY glClearDepth( GLclampd depth )
{
	renderer->GetDepthBuffer().SetClearValue( (float)depth );
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

	renderer->GetDepthBuffer().SetDepthFunc( table[func] );
}

WINGDIAPI void APIENTRY glClearStencil( GLint s )
{
	renderer->GetStencilBuffer().SetClearValue( s );
}

WINGDIAPI void APIENTRY glStencilFunc( GLenum func, GLint ref, GLuint mask )
{
	static const Dictionary<GLenum, Renderer::StencilFunc::Type> table
	{
		{ GL_NEVER, Renderer::StencilFunc::Type::Never },
		{ GL_LESS, Renderer::StencilFunc::Type::Less },
		{ GL_EQUAL, Renderer::StencilFunc::Type::Equal },
		{ GL_LEQUAL, Renderer::StencilFunc::Type::LEqual },
		{ GL_GREATER, Renderer::StencilFunc::Type::Greater },
		{ GL_NOTEQUAL, Renderer::StencilFunc::Type::NotEqual },
		{ GL_GEQUAL, Renderer::StencilFunc::Type::GEqual },
		{ GL_ALWAYS, Renderer::StencilFunc::Type::Always },
	};
	auto face = renderer->GetStencilBuffer().front;
	face.func = Renderer::StencilFunc( table[func], mask );
	face.ref = ref;
}

WINGDIAPI void APIENTRY glStencilMask( GLuint mask )
{
	auto face = renderer->GetStencilBuffer().front;
	face.mask = mask;
}

WINGDIAPI void APIENTRY glStencilOp( GLenum fail, GLenum zfail, GLenum zpass )
{
	static const Dictionary<GLenum, Renderer::StencilOp::Type> table
	{
		{ GL_ZERO, StencilOp::Zero },
		{ GL_KEEP, StencilOp::Keep },
		{ GL_REPLACE, StencilOp::Replace },
		{ GL_INCR, StencilOp::Increase },
		{ GL_DECR, StencilOp::Decrease },
		{ GL_INVERT, StencilOp::Invert},
	};
	
	auto face = renderer->GetStencilBuffer().front;
	face.fail = table[fail];
	face.depthFail = table[zfail];
	face.pass = table[zpass];
}

WINGDIAPI void APIENTRY glMatrixMode( GLenum mode )
{
	switch ( mode )
	{
	case GL_MODELVIEW:
		matrix = &(renderer->modelView);
		return;

	case GL_PROJECTION:
		matrix = &(renderer->projection);
		return;

	default:
	case GL_TEXTURE:
		// not implement
		return;
	}
}

WINGDIAPI void APIENTRY glViewport( GLint x, GLint y, GLsizei width, GLsizei height )
{
	renderer->viewport.Set( x, y, width, height );
}

WINGDIAPI void APIENTRY glLoadIdentity( void )
{
	matrix->Reset();
}

WINGDIAPI void APIENTRY glTranslatef( GLfloat x, GLfloat y, GLfloat z )
{
	matrix->Translate( x, y, z );
}

WINGDIAPI void APIENTRY glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z )
{
	matrix->Rotate( angle, x, y, z );
}

WINGDIAPI void APIENTRY glScalef( GLfloat x, GLfloat y, GLfloat z )
{
	matrix->Scale( x, y, z );
}

WINGDIAPI void APIENTRY glPushMatrix( void )
{
	matrix->Push();
}

WINGDIAPI void APIENTRY glPopMatrix( void )
{
	matrix->Pop();
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

WINGDIAPI void APIENTRY glVertex2f( GLfloat x, GLfloat y )
{
	meshBuilder.Vertex( x, y, 0 );
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

WINGDIAPI void APIENTRY glFlush( void )
{
	meshBuilder.Flush();
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

Vector4 Convert( GLenum format, Vector4 rgba )
{
	switch ( format )
	{
	default:
	case GL_RGBA:
		return rgba;

	case GL_LUMINANCE:
		{
			// ref : https://en.wikipedia.org/wiki/Grayscale
			static const Vector3 conversion( 0.299f, 0.587f, 0.114f );
			const auto l = std::clamp( conversion.Dot( rgba ), 0.f, 1.f );
			return Vector4( l, l, l, 1 );
		}
	}
}

WINGDIAPI void APIENTRY glCopyTexImage2D( GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border )
{
	const Vector2Int min( x + border, y + border );
	for ( auto j = 0; j < height; ++j )
	for ( auto i = 0; i < width; ++i )
	{
		auto color = renderer->GetFrameBuffer().GetPixel( Vector2Int( i, (height - 1) - j ) + min );
		color = Convert( internalFormat, color );
		textureManager.SetPixel( Vector2Int( i, j ), level, color );
	}
}

WINGDIAPI void APIENTRY glTexGeni( GLenum coord, GLenum pname, GLint param )
{
	if ( pname != GL_TEXTURE_GEN_MODE )
	{
		return;
	}

	texcoordGenerator.SetMode( renderer->texture, coord, param );
}

WINGDIAPI void APIENTRY glTexGenfv( GLenum coord, GLenum pname, const GLfloat* params )
{
	if ( pname == GL_TEXTURE_GEN_MODE )
	{
		texcoordGenerator.SetMode( renderer->texture, coord, (GLint)*params );
	}
	else
	{
		texcoordGenerator.SetPlane( renderer->texture, coord, pname, params );
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
	static const Dictionary<GLenum, Renderer::ShadeModel::Type> table
	{
		{ GL_FLAT, Renderer::ShadeModel::Type::Flat },
		{ GL_SMOOTH, Renderer::ShadeModel::Type::Smooth },
	};
	Renderer::ShadeModel::type = table[mode];
}

WINGDIAPI void APIENTRY glHint( GLenum target, GLenum mode )
{
	// Not Implement
}

WINGDIAPI void APIENTRY glLightModelfv( GLenum pname, const GLfloat* params )
{
	switch ( pname )
	{
	case GL_LIGHT_MODEL_AMBIENT:
		renderer->lighting.SetGlobalAmbient( Vector4( params[0], params[1], params[2], params[3] ) );
		return;

	case GL_LIGHT_MODEL_TWO_SIDE:
		return;
	}
}

WINGDIAPI void APIENTRY glLightfv( GLenum light, GLenum pname, const GLfloat *params )
{
	lightManager.Set( light, pname, params );
}

Renderer::Material& GetMaterial( GLenum face )
{
	switch ( face )
	{
	case GL_FRONT:
		return renderer->lighting.front;

	case GL_BACK:
		return renderer->lighting.back;

	default:
		assert( "Invalide material face." && false );
		return renderer->lighting.front;
	}
}

WINGDIAPI void APIENTRY glMaterialfv( GLenum face, GLenum pname, const GLfloat* params )
{
	if ( face == GL_FRONT_AND_BACK )
	{
		glMaterialfv( GL_FRONT, pname, params );
		glMaterialfv( GL_BACK, pname, params );
		return;
	}

	auto& material = GetMaterial( face );
	switch ( pname )
	{
	case GL_AMBIENT:
		material.ambient = Vector4( params );
		return;

	case GL_DIFFUSE:
		material.diffuse = Vector4( params );
		return;

	case GL_SPECULAR:
		material.specular = Vector4( params );
		return;

	case GL_EMISSION:
		material.emissive = Vector4( params );
		return;

	case GL_SHININESS:
		material.SetShininess( params[0] );
		return;

	case GL_AMBIENT_AND_DIFFUSE:
		{
			Vector4 value( params );
			material.ambient = value;
			material.diffuse = value;
			return;
		}

	case GL_COLOR_INDEX:
		return;
	}
}

WINGDIAPI void APIENTRY glMateriali( GLenum face, GLenum pname, GLint param )
{
	if ( pname != GL_SHININESS )
	{
		return;
	}

	GLfloat value[1] = { (float)param };
	glMaterialfv( face, pname, value );
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

WINGDIAPI void APIENTRY glOrtho( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar )
{
	renderer->projection.Ortho( (float)left, (float)right, (float)bottom, (float)top, (float)zNear, (float)zFar );
}

WINGDIAPI void APIENTRY glClipPlane( GLenum plane, const GLdouble* equation )
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
	textureManager.SetImage( -1, components, width, height, format, type, data );
	return 0;
}

void APIENTRY gluPerspective(
	GLdouble fovy,
	GLdouble aspect,
	GLdouble zNear,
	GLdouble zFar )
{
	matrix->Perspective( (float)fovy, (float)aspect, (float)zNear, (float)zFar );
}

void APIENTRY gluLookAt(
	GLdouble eyex,
	GLdouble eyey,
	GLdouble eyez,
	GLdouble centerx,
	GLdouble centery,
	GLdouble centerz,
	GLdouble upx,
	GLdouble upy,
	GLdouble upz )
{
	const Vector3 eye( (float)eyex, (float)eyey, (float)eyez );
	const Vector3 center( (float)centerx, (float)centery, (float)centerz );
	const Vector3 up( (float)upx, (float)upy, (float)upz );
	matrix->LookAt( eye, center, up );
}

std::vector<std::unique_ptr<GLUquadric>> quadrics;
GLUquadric* APIENTRY gluNewQuadric( void )
{
	quadrics.emplace_back( std::make_unique<GLUquadric>() );
	return quadrics[quadrics.size() - 1].get();
}

void APIENTRY gluDeleteQuadric(
	GLUquadric* state )
{
	for ( auto i = quadrics.begin(); i != quadrics.end(); ++i )
	{
		if ( i->get() == state )
		{
			quadrics.erase( i );
			return;
		}
	}
	
	delete state;
}

void APIENTRY gluQuadricNormals(
	GLUquadric* quadObject,
	GLenum              normals )
{
	quadObject->SetNormals( normals );
}

void APIENTRY gluQuadricTexture(
	GLUquadric* quadObject,
	GLboolean           textureCoords )
{
	quadObject->SetTexture( textureCoords );
}

void APIENTRY gluQuadricOrientation(
	GLUquadric* quadObject,
	GLenum              orientation )
{
	quadObject->SetOrientation( orientation );
}

void APIENTRY gluQuadricDrawStyle(
	GLUquadric* quadObject,
	GLenum              drawStyle )
{
	quadObject->SetDrawStyle( drawStyle );
}

void APIENTRY gluCylinder(
	GLUquadric* qobj,
	GLdouble            baseRadius,
	GLdouble            topRadius,
	GLdouble            height,
	GLint               slices,
	GLint               stacks )
{
	qobj->Draw( *renderer, Renderer::Cylinder( (float)baseRadius, (float)topRadius, (float)height ), slices, stacks );
}

void APIENTRY gluDisk(
	GLUquadric* qobj,
	GLdouble            innerRadius,
	GLdouble            outerRadius,
	GLint               slices,
	GLint               loops )
{
	qobj->Draw( *renderer, Renderer::Disc( (float)innerRadius, (float)outerRadius ), slices, loops );
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
	qobj->Draw( *renderer, Renderer::Disc( (float)innerRadius, (float)outerRadius, Degree( (float)startAngle ), Degree( (float)sweepAngle ) ), slices, loops );
}

void APIENTRY gluSphere(
	GLUquadric* qobj,
	GLdouble            radius,
	GLint               slices,
	GLint               stacks )
{
	qobj->Draw( *renderer, Renderer::Sphere( (float)radius ), slices, stacks );
}