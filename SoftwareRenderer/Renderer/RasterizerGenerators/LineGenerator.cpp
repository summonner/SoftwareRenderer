#include "framework.h"
#include "LineGenerator.h"
#include "Renderer/Rasterizer/Line.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	void LineGenerator::Default( VertexBuffer vertices, IRasterizerList& outRasterizers )
	{
		auto numVertices = vertices.size() - 1;
		for ( auto i = 0u; i < numVertices; i += 2 )
		{
			outRasterizers.emplace_back( std::make_unique<Line>( vertices[i], vertices[i + 1] ) );
		}
	}

	void LineGenerator::Strip( VertexBuffer vertices, IRasterizerList& outRasterizers )
	{
		auto numVertices = vertices.size() - 1;
		for ( auto i = 0u; i < numVertices; ++i )
		{
			outRasterizers.emplace_back( std::make_unique<Line>( vertices[i], vertices[i + 1] ) );
		}
	}
	
	void LineGenerator::Loop( VertexBuffer vertices, IRasterizerList& outRasterizers )
	{
		auto numVertices = vertices.size() - 1;
		for ( auto i = 0u; i < numVertices; ++i )
		{
			outRasterizers.emplace_back( std::make_unique<Line>( vertices[i], vertices[i + 1] ) );
		}

		if ( numVertices > 1 )
		{
			outRasterizers.emplace_back( std::make_unique<Line>( vertices[numVertices], vertices[0] ) );
		}
	}
}