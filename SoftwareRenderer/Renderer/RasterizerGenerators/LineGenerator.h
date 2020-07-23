#pragma once
#include "Types.h"

namespace Renderer
{
	class LineGenerator final
	{
	public:
		static void Default( VertexBuffer vertices, IRasterizerList& outRasterizers );
		static void Strip  ( VertexBuffer vertices, IRasterizerList& outRasterizers );
		static void Loop   ( VertexBuffer vertices, IRasterizerList& outRasterizers );
	};
}