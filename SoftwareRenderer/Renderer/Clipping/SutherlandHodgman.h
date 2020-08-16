#pragma once
#include "IPlane.h"

namespace Renderer
{
	class Vertex;
	class PlaneIterator;
	class SutherlandHodgman abstract final
	{
	public:
		static std::vector<Vertex> ClipPolygon( const std::vector<Vertex>& vertices, const PlaneIterator& planes );
		static std::vector<Vertex> ClipLine( const std::vector<Vertex>& vertices, const PlaneIterator& planes );
		static bool ClipPoint( const Vertex& vertex, const PlaneIterator& planes );

	private:
		static void PushIntersect( const Vertex& previous, const Vertex& current, float dotPrevious, float dotCurrent, const IPlane& plane, std::vector<Vertex>& out );
		
	};
}