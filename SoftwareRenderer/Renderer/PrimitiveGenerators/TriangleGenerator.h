#pragma once
#include "Types.h"

namespace Renderer
{
	class TriangleGenerator
	{
	public:
		static void Triangles( VertexBuffer vertices, int startIndex, IPrimitiveList& outPrimitives );
		static void TriangleStrip( VertexBuffer vertices, int startIndex, IPrimitiveList& outPrimitives );
		static void TriangleFan( VertexBuffer vertices, int startIndex, IPrimitiveList& outPrimitives );
	};
}