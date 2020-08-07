#include "framework.h"
#include "glVertexBuffer.h"

Renderer::Vertex glVertexBuffer::operator []( int i ) const
{
	Renderer::Vertex v;
	v.position = vertices->GetVector4( i );
	if ( texcoords != nullptr )
	{
		v.texcoord = texcoords->GetVector2( i );
	}
	if ( colors != nullptr )
	{
		v.color = colors->GetVector4( i );
	}
	if ( normals != nullptr )
	{
		v.normal = normals->GetVector4( i );
	}
	return v;
}
