#pragma once
#include "IPrimitive.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	class Line final : public IPrimitive
	{
	public:
		Line( const Vertex& a, const Vertex& b );
		~Line();

		bool Contains( const Vector2Int& coordinate ) const;

	private:
		Vertex a;
		Vertex b;
		float thickness;
	};

}