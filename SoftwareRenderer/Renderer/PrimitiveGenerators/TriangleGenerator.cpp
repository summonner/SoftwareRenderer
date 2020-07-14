#include "framework.h"
#include "TriangleGenerator.h"
#include "Renderer/Primitives/Triangle.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	void TriangleGenerator::Triangles( VertexBuffer vertices, int startIndex, IPrimitiveList& outPrimitives )
	{
		auto lastIndex = vertices.size() - 2;
		for ( auto i = startIndex; i < lastIndex; i += 3 )
		{
			outPrimitives.push_back( std::make_unique<Triangle>( vertices[i], vertices[i + 1], vertices[i + 2] ) );
		}
	}

	void TriangleGenerator::TriangleStrip( VertexBuffer vertices, int startIndex, IPrimitiveList& outPrimitives )
	{
		auto lastIndex = vertices.size() - 3;
		for ( auto i = startIndex; i < lastIndex; i += 2 )
		{
			outPrimitives.push_back( std::make_unique<Triangle>( vertices[i], vertices[i + 1], vertices[i + 2] ) );
			outPrimitives.push_back( std::make_unique<Triangle>( vertices[i + 2], vertices[i + 1], vertices[i + 3] ) );
		}
	}

	void TriangleGenerator::TriangleFan( VertexBuffer vertices, int startIndex, IPrimitiveList& outPrimitives )
	{
		auto lastIndex = vertices.size() - 1;
		for ( auto i = startIndex + 1; i < lastIndex; i += 1 )
		{
			outPrimitives.push_back( std::make_unique<Triangle>( vertices[startIndex], vertices[i], vertices[i + 1] ) );
		}
	}
}