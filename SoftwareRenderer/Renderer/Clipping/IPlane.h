#pragma once
#include "Math/Vector4.hpp"

namespace Renderer
{
	class Vertex;
	class IPlane abstract
	{
	public:
		virtual ~IPlane();

		virtual float Dot( const Vertex& vertex ) const abstract;
		virtual float DotWithDiff( const Vertex& v1, const Vertex& v2 ) const abstract;
		//Vertex Intersect( const Vertex& previous, const Vertex& current, float dotPrevious, float dotCurrent ) const;
	protected:
	};
}
