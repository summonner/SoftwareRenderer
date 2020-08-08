#pragma once

namespace Renderer
{
	class Mesh;
	class Vertex;
	class SampleMesh abstract final
	{
	public:
		static Mesh SolidCylinder( float base, float top, float height, int slices, int stacks );
		static Mesh WireCylinder( float base, float top, float height, int slices, int stacks );

	private:
		static void Circle( float z, float v, float radius, int slices, std::vector<Vertex>& vertices );
	};
}