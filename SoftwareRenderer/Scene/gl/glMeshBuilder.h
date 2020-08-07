#pragma once
#include "glAdapter.h"
#include "Renderer/Vertex.h"
#include "Renderer/Mesh/Mesh.h"

class glMeshBuilder
{
public:
	glMeshBuilder();
	~glMeshBuilder();

	void Begin( DrawMode mode );
	Renderer::Mesh End();

	void Color( const float r, const float g, const float b, const float a );
	void Texcoord( const float u, const float v );
	void Normal( const float x, const float y, const float z );
	void Vertex( const float x, const float y, const float z );

private:
	DrawMode mode;
	Renderer::Vertex temp;
	std::vector<Renderer::Vertex> vertices;
};

