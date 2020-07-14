#pragma once
#include "IPrimitive.h"

namespace Renderer
{
	class Vertex;
	class Line final : public IPrimitive
	{
	public:
		Line( const Vertex& a, const Vertex& b );
		~Line();

		bool Contains( const Vector2Int& coordinate ) const;

	private:
		const Vertex& a;
		const Vertex& b;
		float thickness;
	};

}