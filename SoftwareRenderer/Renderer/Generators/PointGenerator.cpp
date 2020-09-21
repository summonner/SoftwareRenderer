#include "framework.h"
#include "PointGenerator.h"
#include "Renderer/Geometry/Point.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	void PointGenerator::Default( VertexBuffer vertices, IGeometryList& outRasterizers )
	{
		auto numVertices = vertices.size();
		for ( auto i = 0u; i < numVertices; ++i )
		{
			outRasterizers.emplace_back( std::make_unique<Point>( vertices[i] ) );
		}
	}

	void PointGenerator::SetSize( float size )
	{
		Point::size = size;
	}

	void PointGenerator::SetSmooth( bool smooth )
	{
		Point::smooth = smooth;
	}
}