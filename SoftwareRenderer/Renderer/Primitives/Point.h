#pragma once
#include "IPrimitive.h"

namespace Renderer
{
	class Point final : public IPrimitive
	{
	public:
		Point( float x, float y, float z );

		bool Contains( const Vector2Int& coordinate ) const;

	private:
		float x, y, z;
		float radius;
	};
}