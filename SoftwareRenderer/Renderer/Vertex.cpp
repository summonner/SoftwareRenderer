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

	Vertex::Vertex( const Vertex& left, const Vertex& right, const float t )
		: position( Vector4::Lerp( left.position, right.position, t ) )
		, color( Vector4::Lerp( left.color, right.color, t ) )
		, texcoord( Vector2::Lerp( left.texcoord, right.texcoord, t ) )
		, screen( Vector2Int::Lerp( left.screen, right.screen, t ) )
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

	Vertex Vertex::Lerp( const Vertex& left, const Vertex& right, const float t )
	{
		return Vertex( left, right, t );
	}
}