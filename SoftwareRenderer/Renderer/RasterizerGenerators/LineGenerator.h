#pragma once
#include "Types.h"

namespace Renderer
{
	class LineGenerator final
	{
	public:
		static void Default( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers );
		static void Strip( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers );
		static void Loop( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers );
	};
}