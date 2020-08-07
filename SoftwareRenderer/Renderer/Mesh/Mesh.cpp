#include "framework.h"
#include "Mesh.h"

namespace Renderer
{
	Mesh::Mesh( const DrawMode mode, const std::vector<Vertex>& vertices )
		: drawMode( mode )
		, vertices( vertices )
		, indices()
		, sizeOp( &Mesh::GetNumVertices )
		, indexerOp( &Mesh::GetVertex )
	{
	}

	Mesh::Mesh( const DrawMode mode, const std::vector<Vertex>& vertices, const std::vector<int>& indices )
		: drawMode( mode )
		, vertices( vertices )
		, indices( indices )
		, sizeOp( this->indices.size() > 0 ? &Mesh::GetNumIndices : &Mesh::GetNumVertices )
		, indexerOp( this->indices.size() > 0 ? &Mesh::GetFromIndex : &Mesh::GetVertex )
	{
	}

	Mesh::~Mesh()
	{
	}

	size_t Mesh::GetNumVertices() const
	{
		return vertices.size();
	}

	size_t Mesh::GetNumIndices() const
	{
		return indices.size();
	}

	const Vertex& Mesh::GetVertex( unsigned int index ) const
	{
		return vertices[index];
	}

	const Vertex& Mesh::GetFromIndex( unsigned int index ) const
	{
		const auto i = indices[index];
		assert( i >= 0 && i < vertices.size() );
		return vertices[i];
	}
}