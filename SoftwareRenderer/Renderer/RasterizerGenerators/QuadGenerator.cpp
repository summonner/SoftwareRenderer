#include "framework.h"
#include "QuadGenerator.h"
#include "Renderer/Rasterizer/Triangle.h"
#include "Renderer/Vertex.h"
#include "TriangleGenerator.h"

namespace Renderer
{
	void QuadGenerator::Quads( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers )
	{
		auto lastIndex = endIndex - 3;
		for ( auto i = startIndex; i < lastIndex; i += 4 )
		{
			Build( vertices[i], vertices[i + 1], vertices[i + 2], vertices[i + 3], outRasterizers );
		}
	}
	
	void QuadGenerator::Build( const Vertex& a, const Vertex& b, const Vertex& c, const Vertex& d, IRasterizerList& outRasterizers )
	{
		if ( TriangleGenerator::CheckFacet( a.screen, b.screen, c.screen ) == false )
		{
			return;
		}

		outRasterizers.emplace_back( std::make_unique<Triangle>( a, b, c ) );
		outRasterizers.emplace_back( std::make_unique<Triangle>( a, c, d ) );
	}
}