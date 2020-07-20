#include "framework.h"
#include "LineGenerator.h"
#include "Renderer/Rasterizer/Line.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	void LineGenerator::Default( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers )
	{
		auto numVertices = endIndex - 1;
		for ( auto i = startIndex; i < numVertices; i += 2 )
		{
			outRasterizers.emplace_back( std::make_unique<Line>( vertices[i], vertices[i + 1] ) );
		}
	}

	void LineGenerator::Strip( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers )
	{
		auto numVertices = endIndex - 1;
		for ( auto i = startIndex; i < numVertices; ++i )
		{
			outRasterizers.emplace_back( std::make_unique<Line>( vertices[i], vertices[i + 1] ) );
		}
	}
	
	void LineGenerator::Loop( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers )
	{
		auto numVertices = endIndex - 1;
		for ( auto i = startIndex; i < numVertices; ++i )
		{
			outRasterizers.emplace_back( std::make_unique<Line>( vertices[i], vertices[i + 1] ) );
		}

		if ( numVertices > 1 )
		{
			outRasterizers.emplace_back( std::make_unique<Line>( vertices[numVertices], vertices[startIndex] ) );
		}
	}
}