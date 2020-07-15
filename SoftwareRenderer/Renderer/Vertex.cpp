#include "framework.h"
#include "Vertex.h"
#include "Math/Matrix4x4.h"

namespace Renderer
{
	Vertex::Vertex()
	{
	}

	Vertex::~Vertex()
	{
	}

	void Vertex::Rasterize( const Matrix4x4& view )
	{
		auto screenPosition = view * position;
		screenCoordinate = Vector2( screenPosition.x, screenPosition.y );
		depth = screenPosition.z;
	}
}