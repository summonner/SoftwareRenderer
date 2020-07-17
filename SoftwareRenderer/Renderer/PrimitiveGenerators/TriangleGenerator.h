#pragma once
#include "Types.h"
#include "Math/Vector.h"

namespace Renderer
{
	class TriangleGenerator
	{
	public:
		static void Triangles( VertexBuffer vertices, int startIndex, int endIndex, IPrimitiveList& outPrimitives );
		static void TriangleStrip( VertexBuffer vertices, int startIndex, int endIndex, IPrimitiveList& outPrimitives );
		static void TriangleFan( VertexBuffer vertices, int startIndex, int endIndex, IPrimitiveList& outPrimitives );

		static void Build( const Vertex& a, const Vertex& b, const Vertex& c, IPrimitiveList& outPrimitives );
		static bool CheckClipped( const Vector3& a, const Vector3& b, const Vector3& c );
	};
}