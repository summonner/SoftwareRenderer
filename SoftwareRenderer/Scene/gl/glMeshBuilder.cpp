#include "framework.h"
#include "glMeshBuilder.h"
#include "glBuffer.h"
using namespace Renderer;

const Dictionary<GLenum, DrawMode> glMeshBuilder::table
{
	{ GL_POINTS, DrawMode::Points },
	{ GL_LINES, DrawMode::Lines },
	{ GL_LINE_STRIP, DrawMode::LineStrip },
	{ GL_LINE_LOOP, DrawMode::LineLoop },
	{ GL_TRIANGLES, DrawMode::Triangles },
	{ GL_TRIANGLE_STRIP, DrawMode::TriangleFan },
	{ GL_TRIANGLE_FAN, DrawMode::TriangleFan },
	{ GL_QUADS, DrawMode::Quads },
};

glMeshBuilder::glMeshBuilder()
	: mode( DrawMode::Points )
	, vertices()
{
}

glMeshBuilder::~glMeshBuilder()
{
}

void glMeshBuilder::Begin( GLenum mode )
{
	this->mode = table[mode];
}

Mesh glMeshBuilder::End()
{
	return Mesh( mode, std::move( vertices ) );
}

void glMeshBuilder::Color( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha )
{
	temp.color = Vector4( red, green, blue, alpha );
}

void glMeshBuilder::Texcoord( GLfloat s, GLfloat t )
{
	temp.texcoord = Vector2( s, t );
}

void glMeshBuilder::Normal( GLfloat nx, GLfloat ny, GLfloat nz )
{
	temp.normal = Vector3( nx, ny, nz );
}

void glMeshBuilder::Vertex( GLfloat x, GLfloat y, GLfloat z )
{
	temp.position = Vector4( x, y, z, 1 );
	vertices.push_back( temp );
}

void glMeshBuilder::Color( GLint size, GLenum type, GLsizei stride, const GLvoid* pointer )
{
	buffer.colors = std::make_unique<glBuffer>( size, type, stride, pointer );
}

void glMeshBuilder::Texcoord( GLint size, GLenum type, GLsizei stride, const GLvoid* pointer )
{
	buffer.texcoords = std::make_unique<glBuffer>( size, type, stride, pointer );
}

void glMeshBuilder::Normal( GLenum type, GLsizei stride, const GLvoid* pointer )
{
	buffer.normals = std::make_unique<glBuffer>( 3, type, stride, pointer );
}

void glMeshBuilder::Vertex( GLint size, GLenum type, GLsizei stride, const GLvoid* pointer )
{
	buffer.vertices = std::make_unique<glBuffer>( size, type, stride, pointer );
}

Renderer::Mesh glMeshBuilder::Build( GLenum mode, GLint first, GLsizei count )
{
	vertices.clear();
	vertices.reserve( count );
	const auto end = first + count;
	for ( auto i = first; i < end; ++i )
	{
		vertices.push_back( buffer[i] );
	}

	return Mesh( table[mode], std::move( vertices ) );
}

Renderer::Mesh glMeshBuilder::Build( GLenum mode, GLsizei count, GLenum type, const GLvoid* indices )
{
	const auto inputs = glBuffer( 1, type, 0, indices );
	return Mesh( table[mode], std::move( vertices ) );
}