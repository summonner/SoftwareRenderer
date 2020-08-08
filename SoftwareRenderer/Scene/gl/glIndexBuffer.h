#pragma once
#include "glBuffer.hpp"
#include "Renderer/Mesh/Mesh.h"

class glIndexBuffer final
{
	using Index = Renderer::Mesh::IndexType;
public:
	glIndexBuffer( GLsizei count, GLenum type, const GLvoid* indices );
	~glIndexBuffer();

	std::vector<Index> Extract() const;

private:
	static std::pair<Index, Index> FindMinMax( const IBuffer<Index>& buffer, const GLsizei count );
private:
	const std::unique_ptr<IBuffer<Index>> buffer;
	const GLsizei count;

	struct IndexType;

public:
	const std::pair<Index, Index> minmax;
};

