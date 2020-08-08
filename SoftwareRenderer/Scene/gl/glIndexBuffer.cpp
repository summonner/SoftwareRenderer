#include "framework.h"
#include "glIndexBuffer.h"
#include "glBufferIterator.hpp"

struct glIndexBuffer::IndexType
{
	using Output = Index;
	using Subtype = Index;
	static constexpr Output defaultValue = 0;
};

glIndexBuffer::glIndexBuffer( GLsizei count, GLenum type, const GLvoid* indices )
	: buffer( glBufferFactory::Create<IndexType>( 1, type, 0, indices ) )
	, count( count )
	, minmax( FindMinMax( *buffer, count ) )
{
}

glIndexBuffer::~glIndexBuffer()
{
}

std::pair<glIndexBuffer::Index, glIndexBuffer::Index> glIndexBuffer::FindMinMax( const IBuffer<Index>& buffer, const GLsizei count )
{
	BufferIterator<Index> iterator( buffer, count );
	const auto minmax = std::minmax_element( iterator.begin(), iterator.end() );
	return { *minmax.first, *minmax.second };
}

std::vector<glIndexBuffer::Index> glIndexBuffer::Extract() const
{
	std::vector<Index> index( count );
	for ( auto i = 0; i < count; ++i )
	{
		index[i] = (*buffer)[i] - minmax.first;
	}

	return index;
}