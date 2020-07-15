#include "framework.h"
#include "PointGenerator.h"
#include "Math/Vector4.hpp"
#include "Renderer/Primitives/Point.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	void PointGenerator::Default( VertexBuffer vertices, int startIndex, int endIndex, IPrimitiveList& outPrimitives )
	{
		auto numVertices = endIndex;
		for ( auto i = startIndex; i < numVertices; ++i )
		{
			outPrimitives.push_back( std::make_unique<Point>( vertices[i] ) );
		}
	}
}