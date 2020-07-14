#include "framework.h"
#include "Line.h"
#include "Renderer/Vertex.h"
#include "Math/Vector4.hpp"
#include "Math/Vector2.hpp"

namespace Renderer
{
	Line::Line( const Vertex& a, const Vertex& b )
		: a( a )
		, b( b )
		, thickness( 5.f )
	{
	}

	Line::~Line()
	{
	}

	// realtime collision detection
	// http://www.r-5.org/files/books/computers/algo-list/realtime-3d/Christer_Ericson-Real-Time_Collision_Detection-EN.pdf
	bool Line::Contains( const Vector2Int& c ) const
	{
		auto a = this->a.GetScreenCoordinate();
		auto b = this->b.GetScreenCoordinate();

		auto ab = b - a;
		auto ac = c - a;
		auto t = ac.Dot( ab );
		if ( t < 0 )
		{
			return false;
		//	return ac.Dot( ac ) <= (thickness * thickness);
		}

		auto denom = ab.Dot( ab );
		if ( t > denom )
		{
			return false;
		//	auto bc = c - b;
		//	return bc.Dot( bc ) <= (thickness * thickness);
		}

		auto squaredDistance = ac.Dot( ac ) - t * t / (float)denom;
		return squaredDistance <= (thickness * thickness);
	}
}