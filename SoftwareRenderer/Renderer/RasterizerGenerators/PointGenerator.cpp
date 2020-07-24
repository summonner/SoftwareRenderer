#include "framework.h"
#include "PointGenerator.h"
#include "Renderer/Rasterizer/Point.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	void PointGenerator::Default( VertexBuffer vertices, IRasterizerList& outRasterizers )
	{
		auto numVertices = vertices.size();
		for ( auto i = 0u; i < numVertices; ++i )
		{
			outRasterizers.emplace_back( std::make_unique<Point>( vertices[i] ) );
		}
	}
}