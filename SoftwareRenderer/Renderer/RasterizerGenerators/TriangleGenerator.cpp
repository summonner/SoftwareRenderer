#include "framework.h"
#include "TriangleGenerator.h"
#include "Renderer/Rasterizer/Triangle.h"
#include "Renderer/Vertex.h"
#include "Math/Vector3.hpp"
#include "SutherlanHodgmanClipping.h"

#undef max
#undef min
#define max std::max
#define min std::min

namespace Renderer
{
	void TriangleGenerator::Default( VertexBuffer vertices, IRasterizerList& outRasterizers )
	{
		auto lastIndex = vertices.size() - 2;
		for ( auto i = 0u; i < lastIndex; i += 3 )
		{
			Build( vertices[i], vertices[i + 1], vertices[i + 2], outRasterizers );
		}
	}

	void TriangleGenerator::Strip( VertexBuffer vertices, IRasterizerList& outRasterizers )
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

	void TriangleGenerator::Fan( VertexBuffer vertices, IRasterizerList& outRasterizers )
	{
		auto lastIndex = vertices.size() - 1;
		for ( auto i = 1u; i < lastIndex; i += 1 )
		{
			Build( vertices[0], vertices[i], vertices[i + 1], outRasterizers );
		}
	}

	void TriangleGenerator::Build( const Vertex& a, const Vertex& b, const Vertex& c, IRasterizerList& outRasterizers )
	{
		if ( CheckFacet( a.screen, b.screen, c.screen ) == false )
		{
			return;
		}

		const auto clippedVertices = SutherlandHodgmanClipping::Clip( { a, b, c } );
		if ( clippedVertices.size() < 3 )
		{
			return;
		}

		const auto derivatives = DerivativeTexcoord::Triangle( a, b, c );
		outRasterizers.emplace_back( std::make_unique<Triangle>( clippedVertices, derivatives ) );
	}

	bool TriangleGenerator::CheckFacet( const Vector2Int& a, const Vector2Int& b, const Vector2Int& c )
	{
		auto ab = b - a;
		auto ac = c - a;
		return ab.Area( ac ) > 0.f;
	}
}