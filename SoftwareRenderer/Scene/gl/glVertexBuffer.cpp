#include "framework.h"
#include "glVertexBuffer.h"

Renderer::Vertex glVertexBuffer::operator []( int i ) const
{
	Renderer::Vertex v;
	v.position = (*vertices)[i];
	if ( texcoords != nullptr )
	{
		v.texcoord = (*texcoords)[i];
	}
	if ( colors != nullptr )
	{
		v.color = (*colors)[i];
	}
	if ( normals != nullptr )
	{
		v.normal = (*normals)[i];
	}
	return v;
}
