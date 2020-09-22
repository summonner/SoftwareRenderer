#pragma once
#include "Math/Vector2.hpp"

namespace Renderer
{
	class Vertex;
	class BresenhamCircle final
	{
	public:
		BresenhamCircle( const Vector2Int& center, float radius );
		~BresenhamCircle();

		bool Next();
		bool NextY();

	private:
		const Vector2Int& c;
		const float r;

		Vector2Int next;
		Vector2Int add;
		Vector2Int _p;
		int d;

	public:
		const Vector2Int& p;
	};

}