#include "framework.h"
#include "LineGenerator.h"
#include "Renderer/Primitives/Line.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	void LineGenerator::Default( VertexBuffer vertices, int startIndex, IPrimitiveList& outPrimitives )
	{
		auto numVertices = vertices.size() - 1;
		for ( auto i = startIndex; i < numVertices; i += 2 )
		{
			outPrimitives.push_back( std::make_unique<Line>( vertices[i], vertices[i + 1] ) );
		}
	}

	void LineGenerator::Strip( VertexBuffer vertices, int startIndex, IPrimitiveList& outPrimitives )
	{
		auto numVertices = vertices.size() - 1;
		for ( auto i = startIndex; i < numVertices; ++i )
		{
			outPrimitives.emplace_back( std::make_unique<Line>( vertices[i], vertices[i + 1] ) );
		}
	}
	
	void LineGenerator::Loop( VertexBuffer vertices, int startIndex, IPrimitiveList& outPrimitives )
	{
		auto numVertices = vertices.size() - 1;
		for ( auto i = startIndex; i < numVertices; ++i )
		{
			outPrimitives.emplace_back( std::make_unique<Line>( vertices[i], vertices[i + 1] ) );
		}

		if ( numVertices > 1 )
		{
			outPrimitives.emplace_back( std::make_unique<Line>( vertices[numVertices], vertices[startIndex] ) );
		}
	}
}