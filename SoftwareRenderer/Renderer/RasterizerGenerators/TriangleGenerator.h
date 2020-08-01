#pragma once
#include "Types.h"

namespace Renderer
{
	class TriangleGenerator final abstract
	{
	public:
		static void Default	( VertexBuffer vertices, IRasterizerList& outRasterizers );
		static void Strip	( VertexBuffer vertices, IRasterizerList& outRasterizers );
		static void Fan		( VertexBuffer vertices, IRasterizerList& outRasterizers );

		static void Build( const Vertex& a, const Vertex& b, const Vertex& c, IRasterizerList& outRasterizers );

	public:
		template<typename T>
		static float CheckFacet( const T& a, const T& b, const T& c );
	};
}