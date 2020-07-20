#pragma once
#include "Types.h"
#include "Math/Vector.h"

namespace Renderer
{
	class TriangleGenerator
	{
	public:
		static void Triangles( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers );
		static void TriangleStrip( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers );
		static void TriangleFan( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers );

		static void Build( const Vertex& a, const Vertex& b, const Vertex& c, IRasterizerList& outRasterizers );
		static bool CheckClipped( const Vector3& a, const Vector3& b, const Vector3& c );
	};
}