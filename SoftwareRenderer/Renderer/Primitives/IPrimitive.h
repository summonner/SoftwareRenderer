#pragma once

class Vector2Int;

namespace Renderer
{
	class IPrimitive abstract
	{
	public:
		virtual bool Contains( const Vector2Int& coordinate ) const abstract;
	};
}