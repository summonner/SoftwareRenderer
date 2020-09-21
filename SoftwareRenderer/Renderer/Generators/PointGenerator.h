#pragma once
#include "Types.h"

namespace Renderer 
{
	class PointGenerator final
	{
	public:
		static void Default( VertexBuffer vertices, IGeometryList& outRasterizers );

		static void SetSize( float size );
		static void SetSmooth( bool smooth );
	};
}