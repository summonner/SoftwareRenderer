#pragma once
#include "Types.h"

namespace Renderer
{
	class QuadGenerator final abstract
	{
	public:
		static void Quads( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers );

	private:
		static void Build( const Vertex& a, const Vertex& b, const Vertex& c, const Vertex& d, IRasterizerList& outRasterizers );
	};
}