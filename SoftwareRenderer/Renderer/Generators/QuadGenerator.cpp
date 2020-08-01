#include "framework.h"
#include "QuadGenerator.h"
#include "Renderer/Geometry/Triangle.h"
#include "Renderer/Vertex.h"
#include "TriangleGenerator.h"

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
		TriangleGenerator::Build( a, b, c, outRasterizers );
		TriangleGenerator::Build( a, c, d, outRasterizers );
	}
}