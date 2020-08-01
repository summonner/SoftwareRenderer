#pragma once

namespace Renderer
{
	class Vertex;
	class SutherlandHodgman abstract final
	{
	public:
		static std::vector<Vertex> ClipPolygon( const std::vector<Vertex>& vertices );
		static std::vector<Vertex> ClipLine( const std::vector<Vertex>& vertices );
		static bool ClipPoint( const Vertex& vertex );

	private:
		static void PushIntersect( const Vertex& previous, const Vertex& current, float dotPrevious, const Vector4& plane, std::vector<Vertex>& out );
		static const std::vector<Vector4> clipPlanes;
	};
}