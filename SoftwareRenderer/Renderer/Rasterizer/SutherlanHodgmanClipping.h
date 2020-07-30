#pragma once

namespace Renderer
{
	class Vertex;
	class SutherlandHodgmanClipping abstract final
	{
	public:
		static std::vector<Vertex> Clip( const std::vector<Vertex>& vertices );

	private:
		static const std::vector<Vector4> clipPlanes;
	};
}