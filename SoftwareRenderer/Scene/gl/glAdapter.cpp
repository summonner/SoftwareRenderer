#include "framework.h"
#include "glAdapter.h"
#include "Math/Vector4.hpp"
#include "glBridge.h"
#include "GLUquadric.h"
#include "Renderer/Rasterizer/ShadeModel.h"
#include "glDisplayList.h"
#include "Renderer/Generators/PointGenerator.h"
#include "Renderer/Generators/LineGenerator.h"

glBridge* adapter;
ICommandBuffer* commandBuffer;
#define renderer adapter->renderer
#define textureManager adapter->textureManager
#define lightManager adapter->lightManager
#define meshBuilder adapter->meshBuilder
#define matrix adapter->matrix
#define texcoordGenerator adapter->texcoordGenerator
#define clipPlaneManager adapter->clipPlaneManager
#define displayListManager adapter->displayListManager
#define fogManager adapter->fogManager
#define selectMode adapter->selectMode

void glEnable( GLenum cap, bool enable )
{
	switch ( cap )
	{
	case GL_DEPTH_TEST:
		renderer->GetDepthBuffer().SetEnable( enable );
		break;

	case GL_STENCIL_TEST:
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

	case GL_CLIP_PLANE0:
	case GL_CLIP_PLANE1:
	case GL_CLIP_PLANE2:
	case GL_CLIP_PLANE3:
	case GL_CLIP_PLANE4:
	case GL_CLIP_PLANE5:
		if ( enable == true )
		{
			renderer->planes.Add( clipPlaneManager.Get( cap ) );
		}
		else
		{
			renderer->planes.Remove( clipPlaneManager.Get( cap ) );
		}
		break;

	case GL_COLOR_MATERIAL:
		renderer->lighting.colorMaterial.SetEnable( enable );
		break;

	case GL_FOG:
		renderer->fog.SetEnable( enable );
		if ( enable == true )
		{
			renderer->fog.SetMode( fogManager.GetMode() );
		}
		break;

	case GL_POINT_SMOOTH:
		Renderer::PointGenerator::SetSmooth( enable );
		break;

	case GL_LINE_SMOOTH:
		Renderer::LineGenerator::SetSmooth( enable );
		break;

	case GL_SCISSOR_TEST:
		renderer->viewport.scissor.SetEnable( enable );
		break;

	default:
		assert( false );
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

WINGDIAPI GLboolean APIENTRY glIsEnabled( GLenum cap )
{
	switch ( cap )
	{
	case GL_TEXTURE_2D:
		return renderer->texture.IsEnable();

	default:
		assert( false );
		return false;
	}
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

WINGDIAPI void APIENTRY glDepthMask( GLboolean flag )
{
	renderer->GetDepthBuffer().SetWrite( flag == GL_TRUE );
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
	auto& face = renderer->GetStencilBuffer().front;
	face.func = Renderer::StencilFunc( table[func], mask );
	face.ref = ref;
}

WINGDIAPI void APIENTRY glStencilMask( GLuint mask )
{
	auto& face = renderer->GetStencilBuffer().front;
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
	
	auto& face = renderer->GetStencilBuffer().front;
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

WINGDIAPI void APIENTRY glScissor( GLint x, GLint y, GLsizei width, GLsizei height )
{
	renderer->viewport.scissor.Set( x, y, width, height );
}

WINGDIAPI void APIENTRY glLoadIdentity( void )
{
	auto command = []( glBridge* adapter )
	{
		matrix->Reset();
	};

	commandBuffer->Push( command );
}

WINGDIAPI void APIENTRY glTranslatef( GLfloat x, GLfloat y, GLfloat z )
{
	auto command = [x, y, z]( glBridge* adapter )
	{
		matrix->Translate( x, y, z );
	};

	commandBuffer->Push( command );
}

WINGDIAPI void APIENTRY glTranslated( GLdouble x, GLdouble y, GLdouble z )
{
	glTranslatef( (GLfloat)x, (GLfloat)y, (GLfloat)z );
}

WINGDIAPI void APIENTRY glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z )
{
	auto command = [angle, x, y, z]( glBridge* adapter )
	{
		matrix->Rotate( angle, x, y, z );
	};

	commandBuffer->Push( command );
}

WINGDIAPI void APIENTRY glScalef( GLfloat x, GLfloat y, GLfloat z )
{
	auto command = [x, y, z]( glBridge* adapter )
	{
		matrix->Scale( x, y, z );
	};

	commandBuffer->Push( command );
}

WINGDIAPI void APIENTRY glPushMatrix( void )
{
	auto command = []( glBridge* adapter )
	{
		matrix->Push();
	};

	commandBuffer->Push( command );
}

WINGDIAPI void APIENTRY glPopMatrix( void )
{
	auto command = []( glBridge* adapter )
	{
		matrix->Pop();
	};

	commandBuffer->Push( command );
}

WINGDIAPI void APIENTRY glBegin( GLenum mode )
{
	auto command = [mode]( glBridge* adapter )
	{
		meshBuilder.Begin( mode );
	};

	commandBuffer->Push( command );
}

WINGDIAPI void APIENTRY glColor3f( GLfloat red, GLfloat green, GLfloat blue )
{
	glColor4f( red, green, blue, 1.f );
}

WINGDIAPI void APIENTRY glColor3fv( const GLfloat* v )
{
	glColor4f( v[0], v[1], v[2], 1.f );
}

WINGDIAPI void APIENTRY glColor3ub( GLubyte red, GLubyte green, GLubyte blue )
{
	glColor4f( red / 255.f, green / 255.f, blue / 255.f, 1.f );
}

WINGDIAPI void APIENTRY glColor4f( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
	auto command = [red, green, blue, alpha]( glBridge* adapter )
	{
		meshBuilder.Color( red, green, blue, alpha );
	};

	commandBuffer->Push( command );
}

WINGDIAPI void APIENTRY glColor4ub( GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha )
{
	glColor4f( red / 255.f, green / 255.f, blue / 255.f, alpha / 255.f );
}

WINGDIAPI void APIENTRY glVertex2i( GLint x, GLint y )
{
	glVertex2f( (GLfloat)x, (GLfloat)y );
}

WINGDIAPI void APIENTRY glVertex2f( GLfloat x, GLfloat y )
{
	glVertex3f( x, y, 0 );
}

WINGDIAPI void APIENTRY glVertex2d( GLdouble x, GLdouble y )
{
	glVertex3f( (GLfloat)x, (GLfloat)y, 0 );
}

WINGDIAPI void APIENTRY glVertex3f( GLfloat x, GLfloat y, GLfloat z )
{
	auto command = [x, y, z]( glBridge* adapter )
	{
		meshBuilder.Vertex( x, y, z );
	};

	commandBuffer->Push( command );
}
WINGDIAPI void APIENTRY glVertex3i( GLint x, GLint y, GLint z )
{
	glVertex3f( (GLfloat)x, (GLfloat)y, (GLfloat)z );
}

WINGDIAPI void APIENTRY glVertex3d( GLdouble x, GLdouble y, GLdouble z )
{
	glVertex3f( (GLfloat)x, (GLfloat)y, (GLfloat)z );
}

WINGDIAPI void APIENTRY glVertex3fv( const GLfloat* v )
{
	glVertex3f( v[0], v[1], v[2] );
}

WINGDIAPI void APIENTRY glTexCoord2f( GLfloat s, GLfloat t )
{
	auto command = [s, t]( glBridge* adapter )
	{
		meshBuilder.Texcoord( s, t );
	};

	commandBuffer->Push( command );
}

WINGDIAPI void APIENTRY glTexCoord2d( GLdouble s, GLdouble t )
{
	glTexCoord2f( (GLfloat)s, (GLfloat)t );
}

WINGDIAPI void APIENTRY glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz )
{
	auto command = [nx, ny, nz]( glBridge* adapter )
	{
		meshBuilder.Normal( nx, ny, nz );
	};

	commandBuffer->Push( command );
}

WINGDIAPI void APIENTRY glNormal3fv( const GLfloat* v )
{
	glNormal3f( v[0], v[1], v[2] );
}

WINGDIAPI void APIENTRY glFlush( void )
{
	auto command = []( glBridge* adapter )
	{
		meshBuilder.Flush();
	};

	commandBuffer->Push( command );
}

void Draw( const Renderer::Mesh& mesh )
{
	if ( selectMode.IsEnabled() == false )
	{
		renderer->Draw( mesh );
	}
	else
	{
		IRenderer::RasterizeFunc func = []( Renderer::IRasterizer& rasterizer, const Bounds& bounds )
		{
			selectMode.OnRasterize( rasterizer, bounds );
		};
		renderer->Draw( mesh, func );
	}
}

WINGDIAPI void APIENTRY glEnd( void )
{
	auto command = []( glBridge* adapter )
	{
		const auto mesh = meshBuilder.End();
		Draw( mesh );
	};

	commandBuffer->Push( command );
}

WINGDIAPI void APIENTRY glGenTextures( GLsizei n, GLuint *textures )
{
	textureManager.Generate( n, textures );
}

WINGDIAPI void APIENTRY glBindTexture( GLenum target, GLuint texture )
{
	if ( target != GL_TEXTURE_2D )
	{
		assert( false );
		return;
	}

	auto t = textureManager.Bind( texture );
	renderer->texture.Bind( t );
}

WINGDIAPI void APIENTRY glTexImage2D( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels )
{
	if ( target != GL_TEXTURE_2D )
	{
		assert( false );
		return;
	}

	auto t = textureManager.SetImage( level, internalformat, width, height, format, type, pixels );
	renderer->texture.Bind( t );
}

WINGDIAPI void APIENTRY glTexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels )
{
	if ( target != GL_TEXTURE_2D )
	{
		assert( false );
		return;
	}

	textureManager.SetSubImage( level, xoffset, yoffset, width, height, format, type, pixels );
}

WINGDIAPI void APIENTRY glTexParameteri( GLenum target, GLenum pname, GLint param )
{
	if ( target != GL_TEXTURE_2D )
	{
		assert( false );
		return;
	}

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

WINGDIAPI void APIENTRY glTexParameterf( GLenum target, GLenum pname, GLfloat param )
{
	glTexParameteri( target, pname, (GLint)param );
}

WINGDIAPI void APIENTRY glTexParameterfv( GLenum target, GLenum pname, const GLfloat* params )
{
	// not Implement
}

WINGDIAPI void APIENTRY glTexEnvf( GLenum target, GLenum pname, GLfloat param )
{
	// not Implement
}

WINGDIAPI void APIENTRY glPixelTransferf( GLenum pname, GLfloat param )
{
	switch ( pname )
	{
	case GL_RED_SCALE:
		textureManager.scale.x = param;
		break;
	case GL_GREEN_SCALE:
		textureManager.scale.y = param;
		break;
	case GL_BLUE_SCALE:
		textureManager.scale.z = param;
		break;
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
		auto color = renderer->GetFrameBuffer().GetPixel( Vector2Int( i, j ) + min );
		color = Convert( internalFormat, color );
		textureManager.SetPixel( Vector2Int( i, j ), level, color );
	}
}

WINGDIAPI void APIENTRY glTexGeni( GLenum coord, GLenum pname, GLint param )
{
	if ( pname != GL_TEXTURE_GEN_MODE )
	{
		assert( false );
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

WINGDIAPI void APIENTRY glPolygonMode( GLenum face, GLenum mode )
{
	static const Dictionary<GLenum, PolygonMode> table
	{
		{ GL_FILL, PolygonMode::Fill },
		{ GL_LINE, PolygonMode::Line },
		{ GL_POINT, PolygonMode::Point },
	};

	const auto value = table[mode];
	switch ( face )
	{
		case GL_FRONT:
			renderer->polygonMode.front = value;
			return;

		case GL_BACK:
			renderer->polygonMode.back = value;
			return;

		case GL_FRONT_AND_BACK:
			renderer->polygonMode.front = value;
			renderer->polygonMode.back = value;
			return;
	}
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
	lightManager.Set( light, pname, params, renderer->modelView );
}

WINGDIAPI void APIENTRY glColorMaterial( GLenum face, GLenum mode )
{
	static const Dictionary<GLenum, ColorMaterial> table
	{
		{ GL_AMBIENT_AND_DIFFUSE, ColorMaterial::AmbientAndDiffuse },
		{ GL_AMBIENT, ColorMaterial::Ambient },
		{ GL_DIFFUSE, ColorMaterial::Diffuse },
		{ GL_SPECULAR, ColorMaterial::Specular },
		{ GL_EMISSION, ColorMaterial::Emission },
	};

	const auto value = table[mode];
	switch ( face )
	{
	case GL_FRONT:
		renderer->lighting.colorMaterial.front = value;
		break;

	case GL_BACK:
		renderer->lighting.colorMaterial.back = value;
		break;

	case GL_FRONT_AND_BACK:
		renderer->lighting.colorMaterial.front = value;
		renderer->lighting.colorMaterial.back = value;
		break;
	}
}

WINGDIAPI void APIENTRY glPointSize( GLfloat size )
{
	Renderer::PointGenerator::SetSize( size );
}

WINGDIAPI void APIENTRY glLineWidth( GLfloat width )
{
	Renderer::LineGenerator::SetWidth( width );
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
WINGDIAPI void APIENTRY glMaterialf( GLenum face, GLenum pname, GLfloat param )
{
	if ( pname != GL_SHININESS )
	{
		assert( false );
		return;
	}

	glMaterialfv( face, pname, &param );
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
		assert( false );
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
	Draw( mesh );
}

WINGDIAPI void APIENTRY glDrawElements( GLenum mode, GLsizei count, GLenum type, const GLvoid* indices )
{
	const auto mesh = meshBuilder.Build( mode, count, type, indices );
	Draw( mesh );
}

WINGDIAPI void APIENTRY glEnableClientState( GLenum array )
{
	// TODO
}

WINGDIAPI void APIENTRY glDisableClientState( GLenum array ) 
{
	// TODO
}

WINGDIAPI void APIENTRY glOrtho( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar )
{
	renderer->projection.Ortho( (float)left, (float)right, (float)bottom, (float)top, (float)zNear, (float)zFar );
}

WINGDIAPI void APIENTRY glClipPlane( GLenum plane, const GLdouble* equation )
{
	clipPlaneManager.Set( plane, equation, renderer->modelView );
}

WINGDIAPI GLuint APIENTRY glGenLists( GLsizei range )
{
	return displayListManager.Generate( range );
}

WINGDIAPI void APIENTRY glDeleteLists( GLuint list, GLsizei range )
{
	displayListManager.Delete( list, range );
}

WINGDIAPI void APIENTRY glNewList( GLuint list, GLenum mode )
{
	commandBuffer = displayListManager.Get( list );
}

WINGDIAPI void APIENTRY glEndList( void )
{
	commandBuffer = adapter;
}

WINGDIAPI void APIENTRY glCallList( GLuint list )
{
	auto commands = displayListManager.Get( list );
	commands->Call( adapter );
}

WINGDIAPI void APIENTRY glCallLists( GLsizei n, GLenum type, const GLvoid* lists )
{
	auto commandsList = displayListManager.Get( n, type, lists );
	for ( const auto& commands : commandsList )
	{
		commands->Call( adapter );
	}
}

WINGDIAPI void APIENTRY glListBase( GLuint base )
{
	displayListManager.SetBase( base );
}

WINGDIAPI void APIENTRY glFogf( GLenum pname, GLfloat param )
{
	switch ( pname )
	{
	case GL_FOG_START:
		fogManager.SetStart( param );
		break;

	case GL_FOG_END:
		fogManager.SetEnd( param );
		break;

	case GL_FOG_DENSITY:
		fogManager.SetDensity( param );
		break;
	}
}

WINGDIAPI void APIENTRY glFogfv( GLenum pname, const GLfloat* params )
{
	switch ( pname )
	{
	case GL_FOG_COLOR:
		renderer->fog.SetColor( params );
		break;
	}
}

WINGDIAPI void APIENTRY glFogi( GLenum pname, GLint param )
{
	switch ( pname )
	{
	case GL_FOG_MODE:
		const auto mode = fogManager.SetMode( param );
		renderer->fog.SetMode( mode );
		break;
	}
}

WINGDIAPI void APIENTRY glGetFloatv( GLenum pname, GLfloat* params )
{
	switch ( pname )
	{
	case GL_MODELVIEW_MATRIX:
	{
		const auto modelView = ((Matrix4x4)renderer->modelView).Transpose();
		memcpy( params, &modelView, sizeof( float ) * 16 );
		break;
	}

	default:
		assert( false );
	}
}

WINGDIAPI void APIENTRY glGetIntegerv( GLenum pname, GLint* params )
{
	switch ( pname )
	{
	case GL_VIEWPORT:
	{
		const auto viewport = renderer->viewport.GetBounds();
		params[0] = viewport.x.min;
		params[1] = viewport.y.min;
		params[2] = viewport.x.Length();
		params[3] = viewport.y.Length();
		break;
	}

	default:
		assert( false );
	}
}

WINGDIAPI const GLubyte* APIENTRY glGetString( GLenum name )
{
	static const auto rendererText = "Software Renderer";
	static const auto versionText = "1.0";
	static const auto vendorText = "Dark Summoner";
	static const auto extensionText = "Up/Down - Scroll Texts 1 2 3 4 5 6 7 8 9 10";
	switch ( name )
	{
	case GL_RENDERER:
		return (const GLubyte*)rendererText;
	case GL_VERSION:
		return (const GLubyte*)versionText;
	case GL_VENDOR:
		return (const GLubyte*)vendorText;
	case GL_EXTENSIONS:
		return (const GLubyte*)extensionText;

	default:
		return nullptr;
	}

}

WINGDIAPI GLint APIENTRY glRenderMode( GLenum mode )
{
	assert( mode == GL_RENDER || mode == GL_SELECT );
	return selectMode.SetEnable( mode == GL_SELECT );
}

WINGDIAPI void APIENTRY glSelectBuffer( GLsizei size, GLuint* buffer )
{
	selectMode.SetBuffer( size, buffer );
}

WINGDIAPI void APIENTRY glInitNames( void )
{
	selectMode.InitNames();
}

WINGDIAPI void APIENTRY glPushName( GLuint name )
{
	selectMode.PushName( name );
}

WINGDIAPI void APIENTRY glLoadName( GLuint name )
{
	selectMode.LoadName( name );
}

void APIENTRY gluPickMatrix(
	GLdouble x,
	GLdouble y,
	GLdouble width,
	GLdouble height,
	GLint    viewport[4] )
{
	if ( width <= 0 || height <= 0 )
	{
		return;
	}

	glTranslatef( (GLfloat)((viewport[2] - 2 * (x - viewport[0])) / width), (GLfloat)((viewport[3] - 2 * (y - viewport[1])) / height), 0.f );
	glScalef( (GLfloat)(viewport[2] / width), (GLfloat)(viewport[3] / height), 1.0f );
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
	auto cylinder = Renderer::Cylinder( (float)baseRadius, (float)topRadius, (float)height );
	auto mesh = qobj->Build( *renderer, cylinder, slices, stacks, meshBuilder.GetColor() );
	Draw( mesh );
}

void APIENTRY gluDisk(
	GLUquadric* qobj,
	GLdouble            innerRadius,
	GLdouble            outerRadius,
	GLint               slices,
	GLint               loops )
{
	auto disc = Renderer::Disc( (float)innerRadius, (float)outerRadius );
	auto mesh = qobj->Build( *renderer, disc, slices, loops, meshBuilder.GetColor() );
	Draw( mesh );
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
	auto disc = Renderer::Disc( (float)innerRadius, (float)outerRadius, Degree( (float)startAngle ), Degree( (float)sweepAngle ) );
	auto mesh = qobj->Build( *renderer, disc, slices, loops, meshBuilder.GetColor() );
	Draw( mesh );
}

void APIENTRY gluSphere(
	GLUquadric* qobj,
	GLdouble            radius,
	GLint               slices,
	GLint               stacks )
{
	auto sphere = Renderer::Sphere( (float)radius );
	auto mesh = qobj->Build( *renderer, sphere, slices, stacks, meshBuilder.GetColor() );
	Draw( mesh );
}