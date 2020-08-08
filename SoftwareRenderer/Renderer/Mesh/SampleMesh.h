#pragma once

namespace Renderer
{
	class Mesh;
	class Vertex;
	class IQuadric;
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

	private:
		using BuildFunc = std::function<Mesh( const IQuadric&, int, int )>;
		static Mesh Cylinder( BuildFunc func, float base, float top, float height, int slices, int stacks );
		static Mesh Sphere( BuildFunc func, float radius, int slices, int stacks );
		static Mesh Disc( BuildFunc func, float inner, float outer, int slices, int loops );
		static Mesh PartialDisc( BuildFunc func, float inner, float outer, int slices, int loops, Radian start, Radian sweep );
	};
}