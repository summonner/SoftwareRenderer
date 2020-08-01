#include "framework.h"
#include "Point.h"
#include "Renderer/Rasterizer/PointRasterizer.h"

namespace Renderer
{
	Point::Point( const Vertex& v )
		: v( v )
	{
	}

	Point::~Point()
	{
	}

	std::unique_ptr<IRasterizer> Point::Clip() const
	{
		
		return std::make_unique<PointRasterizer>( v );
	}
}