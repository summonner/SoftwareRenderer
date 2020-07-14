#include "framework.h"
#include "LineGenerator.h"
#include "Renderer/Primitives/Line.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	LineGenerator::LineGenerator()
	{
	}

	LineGenerator::~LineGenerator()
	{
	}

	IPrimitiveList LineGenerator::Generate( VertexBuffer vertices ) const
	{
		return Default( vertices );
	}

	IPrimitiveList LineGenerator::Default( VertexBuffer vertices )
	{
		IPrimitiveList primitives;

		auto numVertices = vertices.size() - 1;
		for ( auto i = 0; i < numVertices; i += 2 )
		{
			primitives.push_back( std::make_unique<Line>( vertices[i], vertices[i + 1] ) );
		}

		return primitives;
	}

	IPrimitiveList LineGenerator::Strip( VertexBuffer vertices )
	{
		IPrimitiveList primitives;

		auto numVertices = vertices.size() - 1;
		for ( auto i = 0; i < numVertices; ++i )
		{
			primitives.emplace_back( std::make_unique<Line>( vertices[i], vertices[i + 1] ) );
		}

		return primitives;
	}
	
	IPrimitiveList LineGenerator::Loop( VertexBuffer vertices )
	{
		IPrimitiveList primitives;

		auto numVertices = vertices.size() - 1;
		for ( auto i = 0; i < numVertices; ++i )
		{
			primitives.emplace_back( std::make_unique<Line>( vertices[i], vertices[i + 1] ) );
		}

		if ( numVertices > 1 )
		{
			primitives.emplace_back( std::make_unique<Line>( vertices[numVertices], vertices[0] ) );
		}

		return primitives;
	}
}