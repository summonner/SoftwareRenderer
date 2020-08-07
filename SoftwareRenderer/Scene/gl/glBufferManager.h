#pragma once
#include "glBuffer.h"
#include "Renderer/Vertex.h"

class glBufferManager
{
public:
	glBufferManager();
	~glBufferManager();

	std::vector<Renderer::Vertex> Build( GLenum mode, GLint first, GLsizei count ) const;

	std::unique_ptr<glBuffer> vertices;
	std::unique_ptr<glBuffer> texcoords;
	std::unique_ptr<glBuffer> colors;
	std::unique_ptr<glBuffer> normals;
};

