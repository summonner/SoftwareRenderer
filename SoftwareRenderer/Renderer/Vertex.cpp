#include "framework.h"
#include "Vertex.h"
#include "Math/Matrix4x4.h"

namespace Renderer
{
	Vertex::Vertex()
		: position( 0, 0, 0, 0 )
		, color( 1, 1, 1, 1 )
		, texcoord( 0, 0 )
		, normal( 0, 0, 0 )
		, view( 0, 0, 0, 0 )
	{
	}

	Vertex::Vertex( const Vertex& left, const Vertex& right, const float t )
		: position( Vector4::Lerp( left.position, right.position, t ) )
		, color( Vector4::Lerp( left.color, right.color, t ) )
		, texcoord( Vector2::Lerp( left.texcoord, right.texcoord, t ) )
		, screen( Vector2Int::Lerp( left.screen, right.screen, t ) )
		, normal( Vector3::Lerp( left.normal, right.normal, t ) )
		, view( Vector4::Lerp( left.view, right.view, t ) )
	{
	}

	Vertex::~Vertex()
	{
	}

	void Vertex::PerspectiveDivide( const Matrix4x4& viewport )
	{
		auto w = 1.f / position.w;
		position *= w;
		color *= w;
		texcoord *= w;

		position = viewport * position;
		screen = Vector2Int( (int)position.x, (int)position.y );
		position.w = w;
	}

	Vertex Vertex::Lerp( const Vertex& left, const Vertex& right, const float t )
	{
		return Vertex( left, right, t );
	}

	Vertex Vertex::Offset( float x, float y ) const
	{
		auto clone = *this;
		clone.position.x += x;
		clone.position.y += y;
		clone.screen = Vector2Int( (int)clone.position.x, (int)clone.position.y );
		return clone;
	}
}