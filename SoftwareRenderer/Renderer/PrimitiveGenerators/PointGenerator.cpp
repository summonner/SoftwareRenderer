#include "framework.h"
#include "PointGenerator.h"
#include "Math/Vector4.hpp"
#include "Renderer/Primitives/Point.h"

namespace Renderer
{
	PointGenerator::PointGenerator()
	{
	}


	PointGenerator::~PointGenerator()
	{
		primitives.clear();
	}

	void PointGenerator::AddVertex( const Vector4& vertex )
	{
		primitives.push_back( std::make_unique<Point>( vertex.x, vertex.y, vertex.z ) );
	}

	IPrimitiveList PointGenerator::Flush()
	{
		return std::move( primitives );
	}
}