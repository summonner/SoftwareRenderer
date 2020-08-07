#pragma once
#include "glAdapter.h"
#include "glVertexBuffer.h"
#include "Renderer/Vertex.h"
#include "Renderer/Mesh/Mesh.h"

class glMeshBuilder
{
public:
	glMeshBuilder();
	~glMeshBuilder();

	void Begin( GLenum mode );
	Renderer::Mesh End();

	void Color( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );
	void Texcoord( GLfloat s, GLfloat t );
	void Normal( GLfloat nx, GLfloat ny, GLfloat nz );
	void Vertex( GLfloat x, GLfloat y, GLfloat z );

	void Color( GLint size, GLenum type, GLsizei stride, const GLvoid* pointer );
	void Texcoord( GLint size, GLenum type, GLsizei stride, const GLvoid* pointer );
	void Normal( GLenum type, GLsizei stride, const GLvoid* pointer );
	void Vertex( GLint size, GLenum type, GLsizei stride, const GLvoid* pointer );
	
	Renderer::Mesh Build( GLenum mode, GLint first, GLsizei count );
	Renderer::Mesh Build( GLenum mode, GLsizei count, GLenum type, const GLvoid* indices );

private:
	DrawMode mode;
	Renderer::Vertex temp;
	std::vector<Renderer::Vertex> vertices;

	glVertexBuffer buffer;

private:
	static const Dictionary<GLenum, DrawMode> table;

	struct ColorType;
	struct TexcoordType;
	struct NormalType;
	struct VertexType;
	struct IndexType;
};

