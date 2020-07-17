#pragma once
#include "Math/Vector2.hpp"

namespace Renderer
{
	class Bresenham final
	{
	public:
		Bresenham( const Vector2Int& a, const Vector2Int& b );
		~Bresenham();

		bool Next();

	private:
		const Vector2Int b;
		const Vector2Int diff;
		const Vector2Int sign;
		int d;

	public:
		Vector2Int p;
	};
}