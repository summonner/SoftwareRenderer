#include "framework.h"
#include "Point.h"
#include "Math/Vector2.hpp"
#include "Renderer/Vertex.h"
#include "RasterizedPixel.h"

namespace Renderer
{
	Point::Point( const Vertex& v )
	{
		pixels.push_back( RasterizedPixel( v.screen, v.color, v.depth ) );
	}

	Point::~Point()
	{
	}
}