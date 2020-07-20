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
		ndc = ndc / ndc.w;
		clip = ndc;

		auto p = viewport * ndc;
		screen = Vector2( p.x, p.y );
		depth = -clip.z + 1.f;
	}
}