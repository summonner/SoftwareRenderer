#include "framework.h"
#include "Vertex.h"
#include "Math/Matrix4x4.h"

namespace Renderer
{
	Vertex::Vertex()
		: color( 1, 1, 1, 1 )
		, depth( 0 )
		, texcoord( 0, 0 )
	{
	}

	Vertex::~Vertex()
	{
	}

	void Vertex::Process( const Matrix4x4& projection, const Matrix4x4& viewport )
	{
		clip = projection * position;
		auto w = 1.f / clip.w;
		clip = clip * w;

		auto p = viewport * clip;
		screen = Vector2( p.x, p.y );
		depth = clip.z;
		clip.w = w;
	}
}