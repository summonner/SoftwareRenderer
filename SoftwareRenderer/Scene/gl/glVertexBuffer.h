#pragma once
#include "glBuffer.h"

struct glVertexBuffer
{
	Renderer::Vertex operator []( int i ) const;

	std::unique_ptr<glBuffer> vertices;
	std::unique_ptr<glBuffer> texcoords;
	std::unique_ptr<glBuffer> colors;
	std::unique_ptr<glBuffer> normals;
};

