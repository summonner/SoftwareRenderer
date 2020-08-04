#include "framework.h"
#include "Point.h"
#include "Renderer/Rasterizer/PointRasterizer.h"
#include "SutherlanHodgman.h"

namespace Renderer
{
	Point::Point( const Vertex& v )
		: v( v )
	{
	}

	Point::~Point()
	{
	}

	std::unique_ptr<IRasterizer> Point::Clip( const Matrix4x4& viewport ) const
	{
		if ( SutherlandHodgman::ClipPoint( v ) == false )
		{
			return nullptr;
		}

		auto vertex = v;
		vertex.PerspectiveDivide( viewport );

		return std::make_unique<PointRasterizer>( vertex );
	}
}