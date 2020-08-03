#include "framework.h"
#include "TriangleGenerator.h"
#include "Renderer/Geometry/Triangle.h"
#include "Renderer/Vertex.h"
#include "Math/Vector3.hpp"

namespace Renderer
{
	void TriangleGenerator::Default( VertexBuffer vertices, IGeometryList& outRasterizers )
	{
		auto lastIndex = vertices.size() - 2;
		for ( auto i = 0u; i < lastIndex; i += 3 )
		{
			Build( vertices[i], vertices[i + 1], vertices[i + 2], outRasterizers );
		}
	}

	void TriangleGenerator::Strip( VertexBuffer vertices, IGeometryList& outRasterizers )
	{
		auto lastIndex = vertices.size() - 3;
		auto i = 0u;
		for ( ; i < lastIndex; i += 2 )
		{
			Build( vertices[i], vertices[i + 1], vertices[i + 2], outRasterizers );
			Build( vertices[i + 2], vertices[i + 1], vertices[i + 3], outRasterizers );
		}

		if ( i == lastIndex )
		{
			Build( vertices[i], vertices[i + 1], vertices[i + 2], outRasterizers );
		}
	}

	void TriangleGenerator::Fan( VertexBuffer vertices, IGeometryList& outRasterizers )
	{
		auto lastIndex = vertices.size() - 1;
		for ( auto i = 1u; i < lastIndex; i += 1 )
		{
			Build( vertices[0], vertices[i], vertices[i + 1], outRasterizers );
		}
	}

	void TriangleGenerator::Build( const Vertex& a, const Vertex& b, const Vertex& c, IGeometryList& outRasterizers )
	{
		outRasterizers.emplace_back( std::make_unique<Triangle>( a, b, c ) );
	}
}