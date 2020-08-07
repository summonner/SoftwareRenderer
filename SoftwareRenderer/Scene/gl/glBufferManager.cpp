#include "framework.h"
#include "glBufferManager.h"

glBufferManager::glBufferManager()
{
}


glBufferManager::~glBufferManager()
{
}

std::vector<Renderer::Vertex> glBufferManager::Build( GLenum mode, GLint first, GLsizei count ) const
{
	std::vector<Renderer::Vertex> result;
	result.reserve( count );

	const auto end = first + count;
	for ( auto i = first; i < end; ++i )
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
		result.push_back( v );
	}

	return result;
}
