#include "framework.h"
#include "Line.h"
#include "Renderer/Vertex.h"
#include "Math/Vector4.hpp"
#include "Math/Vector2.hpp"
#include "Bresenham.h"
#include "RasterizedPixel.h"

namespace Renderer
{
	Line::Line( const Vertex& a, const Vertex& b )
	{
		auto e = Bresenham( a, b );
		do {
			pixels.push_back( RasterizedPixel( e.p, e.GetColor(), e.GetDepth() ) );
		} while ( e.Next() );
	}

	Line::~Line()
	{
	}
}