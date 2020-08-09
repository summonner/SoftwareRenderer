#pragma once
#include "Mesh.h"
namespace Renderer
{
	class Mesh;
	class Vertex;
	class Quadric;
	class SampleMesh abstract final
	{
	public:
		static Mesh SolidCylinder( float base, float top, float height, int slices, int stacks );
		static Mesh WireCylinder( float base, float top, float height, int slices, int stacks );

		static Mesh SolidSphere( float radius, int slices, int stacks );
		static Mesh WireSphere( float radius, int slices, int stacks );

		static Mesh SolidDisc( float inner, float outer, int slices, int loops );
		static Mesh WireDisc( float inner, float outer, int slices, int loops );

		static Mesh SolidPartialDisc( float inner, float outer, int slices, int loops, Degree start, Degree sweep );
		static Mesh WirePartialDisc( float inner, float outer, int slices, int loops, Degree start, Degree sweep );
	};
}