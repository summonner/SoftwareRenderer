#pragma once
#include "VertexIterator.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	class Vertex;
	class Mesh final
	{
		using IndexType = unsigned short;
	public:
		enum class DrawMode
		{
			Points,
			Lines,
			LineStrip,
			LineLoop,
			Triangles,
			TriangleStrip,
			TriangleFan,
			Quads,
		};		

	public:
		Mesh( DrawMode mode, const std::vector<Vertex>& vertices );
		Mesh( DrawMode mode, std::vector<Vertex>&& vertices );
		Mesh( DrawMode mode, const std::vector<Vertex>& vertices, const std::vector<IndexType>& indices );
		Mesh( DrawMode mode, std::vector<Vertex>&& vertices, std::vector<IndexType>&& indices );
		~Mesh();

		inline size_t size() const
		{
			return sizeOp( *this );
		}

		inline const Vertex& operator []( unsigned int index ) const
		{
			return indexerOp( *this, index );
		}

		inline VertexIterator begin() const
		{
			return VertexIterator( *this, 0 );
		}

		inline VertexIterator end() const
		{
			return VertexIterator( *this, size() );
		}

		const DrawMode drawMode;

	private:
		const std::vector<Vertex> vertices;
		const std::vector<IndexType> indices;

		const std::function<size_t( const Mesh& )> sizeOp;
		size_t GetNumVertices() const;
		size_t GetNumIndices() const;

		const std::function<const Vertex& (const Mesh&, unsigned int)> indexerOp;
		const Vertex& GetVertex( unsigned int index ) const;
		const Vertex& GetFromIndex( unsigned int index ) const;
	};
}

using DrawMode = Renderer::Mesh::DrawMode;