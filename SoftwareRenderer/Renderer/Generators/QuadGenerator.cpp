#include "framework.h"
#include "QuadGenerator.h"
#include "Renderer/Geometry/Quad.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	void QuadGenerator::Quads( VertexBuffer vertices, IGeometryList& outRasterizers )
	{
		auto lastIndex = vertices.size() - 3;
		for ( auto i = 0u; i < lastIndex; i += 4 )
		{
			Build( vertices[i], vertices[i + 1], vertices[i + 2], vertices[i + 3], outRasterizers );
		}
	}
	
	void QuadGenerator::Build( const Vertex& a, const Vertex& b, const Vertex& c, const Vertex& d, IGeometryList& outRasterizers )
	{
		outRasterizers.emplace_back( std::make_unique<Quad>( a, b, c, d ) );
	}
}