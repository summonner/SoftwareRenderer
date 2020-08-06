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
		v.texcoord = texcoords->GetVector2( i );
		result.push_back( v );
	}

	return result;
}
