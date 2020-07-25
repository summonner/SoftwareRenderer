#include "framework.h"
#include "Vertex.h"
#include "Math/Matrix4x4.h"

namespace Renderer
{
	Vertex::Vertex()
		: position( 0, 0, 0, 0 )
		, color( 1, 1, 1, 1 )
		, texcoord( 0, 0 )
	{
	}

	Vertex::~Vertex()
	{
	}

	void Vertex::Process( const Matrix4x4& projection, const Matrix4x4& viewport )
	{
		position = projection * position;
		auto w = 1.f / position.w;
		position *= w;
		color *= w;
		texcoord *= w;

		auto p = viewport * position;
		screen = Vector2Int( (int)p.x, (int)p.y );
		position.w = w;
	}
}