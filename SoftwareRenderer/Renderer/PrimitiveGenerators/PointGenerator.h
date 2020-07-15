#pragma once
#include "Types.h"

namespace Renderer 
{
	class PointGenerator final
	{
	public:
		static void Default( VertexBuffer vertices, int startIndex, int endIndex, IPrimitiveList& outPrimitives );
	};
}