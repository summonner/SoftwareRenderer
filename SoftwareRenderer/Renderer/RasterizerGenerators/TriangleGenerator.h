#pragma once
#include "Types.h"

namespace Renderer
{
	class TriangleGenerator final abstract
	{
	public:
		static void Default	( VertexBuffer vertices, IRasterizerList& outRasterizers );
		static void Strip	( VertexBuffer vertices, IRasterizerList& outRasterizers );
		static void Fan		( VertexBuffer vertices, IRasterizerList& outRasterizers );

	private:
		static void Build( const Vertex& a, const Vertex& b, const Vertex& c, IRasterizerList& outRasterizers );

	public:
		static bool CheckFacet( const Vector2Int& a, const Vector2Int& b, const Vector2Int& c );
	};
}