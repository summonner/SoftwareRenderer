#include "framework.h"
#include "Vertex.h"
#include "Math/Matrix4x4.h"

namespace Renderer
{
	Vertex::Vertex()
		: color( 1, 1, 1, 1 )
	{
	}

	Vertex::~Vertex()
	{
	}

	void Vertex::Process( const Matrix4x4& projection, const Matrix4x4& viewport )
	{
		auto ndc = projection * position;
		clipCoordinate = ndc / ndc.w;

		auto screen = viewport * clipCoordinate;
		screenCoordinate = Vector2( screen.x, screen.y );
		depth = (int)(screen.z * INT_MAX);
	}
}