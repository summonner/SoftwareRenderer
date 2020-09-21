#pragma once
#include "Types.h"

namespace Renderer
{
	class LineGenerator final
	{
	public:
		static void Default( VertexBuffer vertices, IGeometryList& outRasterizers );
		static void Strip  ( VertexBuffer vertices, IGeometryList& outRasterizers );
		static void Loop   ( VertexBuffer vertices, IGeometryList& outRasterizers );

		static void SetWidth( float width );
		static void SetSmooth( bool smooth );
	};
}