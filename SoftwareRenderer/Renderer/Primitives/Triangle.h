#pragma once
#include "IPrimitive.h"

namespace Renderer
{
	class Vertex;
	class Triangle final : public IPrimitive
	{
	public:
		Triangle( const Vertex& a, const Vertex& b, const Vertex& c );
		~Triangle();

		bool Contains( const Vector2Int& coordinate ) const override;

	private:
		Vector3 Barycentric( const Vector2Int& coordinate ) const;

	private:
		const Vertex& a;
		const Vertex& b;
		const Vertex& c;
	};

}