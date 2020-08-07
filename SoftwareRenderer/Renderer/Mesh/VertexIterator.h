#pragma once
#include "Util/IBaseIterator.h"

namespace Renderer
{
	class Mesh;
	class Vertex;
	class VertexIterator final : public IBaseIterator<VertexIterator, const Vertex&>
	{
	public:
		VertexIterator( const Mesh& mesh, int index );
		~VertexIterator();

		bool operator !=( const VertexIterator& other ) const;
		const VertexIterator& operator ++();
		const Vertex& operator *() const;
		int operator -( const VertexIterator& other ) const;

		using iterator_category = std::random_access_iterator_tag;
		using value_type = const Vertex;
		using difference_type = int;
		using pointer = const Vertex*;
		using reference = const Vertex&;
	private:
		const Mesh& mesh;
		int index;
	};
}