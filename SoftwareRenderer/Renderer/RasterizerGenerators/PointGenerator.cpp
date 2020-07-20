#include "framework.h"
#include "PointGenerator.h"
#include "Math/Vector4.hpp"
#include "Renderer/Rasterizer/Point.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	void PointGenerator::Default( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers )
	{
		auto numVertices = endIndex;
		for ( auto i = startIndex; i < numVertices; ++i )
		{
			outRasterizers.emplace_back( std::make_unique<Point>( vertices[i] ) );
		}
	}
}