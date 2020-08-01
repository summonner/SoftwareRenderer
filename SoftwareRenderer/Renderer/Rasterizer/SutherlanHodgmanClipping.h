#pragma once

namespace Renderer
{
	class Vertex;
	class SutherlandHodgmanClipping abstract final
	{
	public:
		static std::vector<Vertex> Clip( const std::vector<Vertex>& vertices );

	private:
		static void PushIntersect( const Vertex& previous, const Vertex& current, float dotPrevious, const Vector4& plane, std::vector<Vertex>& out );
		static const std::vector<Vector4> clipPlanes;
	};
}