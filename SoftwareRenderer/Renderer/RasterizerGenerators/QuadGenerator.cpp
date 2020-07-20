#include "framework.h"
#include "QuadGenerator.h"
#include "Renderer/Rasterizer/Triangle.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	void QuadGenerator::Quads( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers )
	{
		auto lastIndex = endIndex - 3;
		for ( auto i = startIndex; i < lastIndex; i += 4 )
		{
			outRasterizers.emplace_back( std::make_unique<Triangle>( vertices[i], vertices[i + 1], vertices[i + 2] ) );
			outRasterizers.emplace_back( std::make_unique<Triangle>( vertices[i], vertices[i + 2], vertices[i + 3] ) );
		}
	}
}