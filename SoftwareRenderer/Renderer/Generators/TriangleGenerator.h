#pragma once
#include "Types.h"

namespace Renderer
{
	class TriangleGenerator final abstract
	{
	public:
		static void Default	( VertexBuffer vertices, IGeometryList& outRasterizers );
		static void Strip	( VertexBuffer vertices, IGeometryList& outRasterizers );
		static void Fan		( VertexBuffer vertices, IGeometryList& outRasterizers );

		static void Build( const Vertex& a, const Vertex& b, const Vertex& c, IGeometryList& outRasterizers );

	public:
		template<typename T>
		static float CheckFacet( const T& a, const T& b, const T& c );
	};
}