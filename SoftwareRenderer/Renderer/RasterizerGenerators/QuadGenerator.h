#pragma once
#include "Types.h"

namespace Renderer
{
	class QuadGenerator final abstract
	{
	public:
		static void Quads( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers );
	};
}