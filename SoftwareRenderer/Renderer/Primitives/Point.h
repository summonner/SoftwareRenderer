#pragma once
#include "IPrimitive.h"

namespace Renderer
{
	class Vertex;
	class Point final : public IPrimitive
	{
	public:
		Point( const Vertex& v );

		bool Contains( const Vector2Int& coordinate ) const;

	private:
		const Vertex& v;
		float radius;
	};
}