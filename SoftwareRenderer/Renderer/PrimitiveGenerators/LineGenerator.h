#pragma once
#include "Types.h"

namespace Renderer
{
	class LineGenerator final
	{
	public:
		static void Default( VertexBuffer vertices, int startIndex, IPrimitiveList& outPrimitives );
		static void Strip( VertexBuffer vertices, int startIndex, IPrimitiveList& outPrimitives );
		static void Loop( VertexBuffer vertices, int startIndex, IPrimitiveList& outPrimitives );
	};
}