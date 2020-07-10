#pragma once
#include "Math/Vector.h"

namespace Renderer
{
	class IPrimitive abstract
	{
	public:
		virtual bool Contains( const Vector2Int& coordinate ) const abstract;
	};
}