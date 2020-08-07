#include "framework.h"
#include "glMeshBuilder.h"
using namespace Renderer;

glMeshBuilder::glMeshBuilder()
	: mode( DrawMode::Points )
	, vertices()
{
}

glMeshBuilder::~glMeshBuilder()
{
}

void glMeshBuilder::Begin( DrawMode mode )
{
	this->mode = mode;
}

Mesh glMeshBuilder::End()
{
	return Mesh( mode, std::move( vertices ) );
}

void glMeshBuilder::Color( const float r, const float g, const float b, const float a )
{
	temp.color = Vector4( r, g, b, a );
}

void glMeshBuilder::Texcoord( const float u, const float v )
{
	temp.texcoord = Vector2( u, v );
}

void glMeshBuilder::Normal( const float x, const float y, const float z )
{
	temp.normal = Vector3( x, y, z );
}

void glMeshBuilder::Vertex( const float x, const float y, const float z )
{
	temp.position = Vector4( x, y, z, 1 );
	vertices.push_back( temp );
}