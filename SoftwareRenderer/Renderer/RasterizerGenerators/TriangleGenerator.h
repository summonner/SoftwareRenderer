#pragma once
#include "Types.h"

namespace Renderer
{
	class TriangleGenerator final abstract
	{
	public:
		static void Triangles( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers );
		static void TriangleStrip( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers );
		static void TriangleFan( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers );

	private:
		static void Build( const Vertex& a, const Vertex& b, const Vertex& c, IRasterizerList& outRasterizers );

	public:
		static bool CheckFacet( const Vector2Int& a, const Vector2Int& b, const Vector2Int& c );
	};
}