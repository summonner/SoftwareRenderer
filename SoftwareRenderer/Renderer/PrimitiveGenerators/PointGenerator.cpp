#include "framework.h"
#include "PointGenerator.h"
#include "Math/Vector4.hpp"
#include "Renderer/Primitives/Point.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	PointGenerator::PointGenerator()
	{
	}


	PointGenerator::~PointGenerator()
	{
	}

	IPrimitiveList PointGenerator::Generate( VertexBuffer vertices ) const
	{
		return Default( vertices );
	}

	IPrimitiveList PointGenerator::Default( VertexBuffer vertices )
	{
		IPrimitiveList primitives;
		for ( const auto& vertex : vertices )
		{
			primitives.push_back( std::make_unique<Point>( vertex ) );
		}

		return primitives;
	}


}