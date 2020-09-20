#include "framework.h"
#include "glMeshBuilder.h"
#include "Buffer/glIndexBuffer.h"
using namespace Renderer;

const Dictionary<GLenum, DrawMode> glMeshBuilder::table
{
	{ GL_POINTS, DrawMode::Points },
	{ GL_LINES, DrawMode::Lines },
	{ GL_LINE_STRIP, DrawMode::LineStrip },
	{ GL_LINE_LOOP, DrawMode::LineLoop },
	{ GL_TRIANGLES, DrawMode::Triangles },
	{ GL_TRIANGLE_STRIP, DrawMode::TriangleStrip },
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

struct glMeshBuilder::ColorType
{
	using Output = Vector4;
	using Subtype = float;
	static constexpr Output defaultValue = Vector4( 0, 0, 0, 1 );
};

struct glMeshBuilder::TexcoordType
{
	using Output = Vector2;
	using Subtype = float;
	static constexpr Output defaultValue = Vector2();
};

struct glMeshBuilder::NormalType
{
	using Output = Vector3;
	using Subtype = float;
	static constexpr Output defaultValue = Vector3();
};

struct glMeshBuilder::VertexType
{
	using Output = Vector4;
	using Subtype = float;
	static constexpr Output defaultValue = Vector4( 0, 0, 0, 1 );
};

void glMeshBuilder::Color( GLint size, GLenum type, GLsizei stride, const GLvoid* pointer )
{
	vertexDatas.colors = glBufferFactory::Create<ColorType>( size, type, stride, pointer );
}

void glMeshBuilder::Texcoord( GLint size, GLenum type, GLsizei stride, const GLvoid* pointer )
{
	vertexDatas.texcoords = glBufferFactory::Create<TexcoordType>( size, type, stride, pointer );
}

void glMeshBuilder::Normal( GLenum type, GLsizei stride, const GLvoid* pointer )
{
	vertexDatas.normals = glBufferFactory::Create<NormalType>( 3, type, stride, pointer );
}

void glMeshBuilder::Vertex( GLint size, GLenum type, GLsizei stride, const GLvoid* pointer )
{
	vertexDatas.vertices = glBufferFactory::Create<VertexType>( size, type, stride, pointer );
}

void glMeshBuilder::Flush()
{
	vertexDatas.vertices = nullptr;
	vertexDatas.normals = nullptr;
	vertexDatas.texcoords = nullptr;
	vertexDatas.colors = nullptr;

	temp = Renderer::Vertex();
	vertices.clear();
}

Renderer::Mesh glMeshBuilder::Build( GLenum mode, GLint first, GLsizei count )
{
	ExtractVertex( first, first + count );
	return Mesh( table[mode], std::move( vertices ) );
}

Renderer::Mesh glMeshBuilder::Build( GLenum mode, GLsizei count, GLenum type, const GLvoid* indices )
{
	const auto indexBuffer = glIndexBuffer( count, type, indices );
	ExtractVertex( indexBuffer.minmax.first, indexBuffer.minmax.second + 1 );
	return Mesh( table[mode], std::move( vertices ), indexBuffer.Extract() );
}

const Vector4& glMeshBuilder::GetColor() const
{
	return temp.color;
}

void glMeshBuilder::ExtractVertex( const int start, const int end )
{
	vertices.clear();
	vertices.reserve( end - start );
	for ( auto i = start; i < end; ++i )
	{
		vertices.push_back( vertexDatas[i] );
	}
}