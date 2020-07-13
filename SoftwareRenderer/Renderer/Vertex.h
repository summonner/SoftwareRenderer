#pragma once
#include "Math/Vector3.hpp"

namespace Renderer
{
	class Vertex final
	{
	public:
		Vertex( const Vector3& position );
		Vertex( const Vector4& position );
		~Vertex();

		Vector2Int GetScreenCoordinate() const;

	private:
		Vector3 position;
	};

}