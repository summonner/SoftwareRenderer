#include "framework.h"
#include "VertexIterator.h"
#include "Mesh.h"


namespace Renderer
{
	VertexIterator::VertexIterator( const Mesh& mesh, int index )
		: mesh( mesh )
		, index( index )
	{
	}

	VertexIterator::~VertexIterator()
	{
	}

	bool VertexIterator::operator !=( const VertexIterator& other ) const
	{
		return index != other.index;
	}

	const Vertex& VertexIterator::operator*() const
	{
		return mesh[index];
	}

	const VertexIterator& VertexIterator::operator++()
	{
		++index;
		return *this;
	}

	int VertexIterator::operator -( const VertexIterator& other ) const
	{
		return other.index - index;
	}
}