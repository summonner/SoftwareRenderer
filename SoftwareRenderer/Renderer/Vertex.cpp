#include "framework.h"
#include "Vertex.h"
#include "Math/Vector2.hpp"
#include "Math/Vector4.hpp"

namespace Renderer
{
	Vertex::Vertex( const Vector3& position )
		: position( position )
	{
	}

	Vertex::Vertex( const Vector4& position )
		: Vertex( Vector3( position.x, position.y, position.z ) )
	{
	}

	Vertex::~Vertex()
	{
	}

	Vector2Int Vertex::GetScreenCoordinate() const
	{
		return Vector2Int( position.x, position.y );
	}
}