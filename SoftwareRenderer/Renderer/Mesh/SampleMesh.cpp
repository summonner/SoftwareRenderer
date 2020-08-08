#include "framework.h"
#include "SampleMesh.h"
#include "Quadric.h"
#include "Mesh.h"

namespace Renderer
{
	Mesh SampleMesh::SolidCylinder( float base, float top, float height, int slices, int stacks )
	{
		return Cylinder( IQuadric::Solid, base, top, height, slices, stacks );
	}

	Mesh SampleMesh::WireCylinder( float base, float top, float height, int slices, int stacks )
	{
		return Cylinder( IQuadric::Wire, base, top, height, slices, stacks );
	}

	Mesh SampleMesh::Cylinder( BuildFunc func, float base, float top, float height, int slices, int stacks )
	{
		Renderer::Cylinder quadric( base, top, height );
		return func( quadric, slices, stacks );
	}


	Mesh SampleMesh::SolidSphere( float radius, int slices, int stacks )
	{
		return Sphere( IQuadric::Solid, radius, slices, stacks );
	}

	Mesh SampleMesh::WireSphere( float radius, int slices, int stacks )
	{
		return Sphere( IQuadric::Wire, radius, slices, stacks );
	}

	Mesh SampleMesh::Sphere( BuildFunc func, float radius, int slices, int stacks )
	{
		Renderer::Sphere quadric( radius );
		return func( quadric, slices, stacks );
	}


	Mesh SampleMesh::SolidDisc( float inner, float outer, int slices, int loops )
	{
		return Disc( IQuadric::Solid, inner, outer, slices, loops );
	}

	Mesh SampleMesh::WireDisc( float inner, float outer, int slices, int loops )
	{
		return Disc( IQuadric::Wire, inner, outer, slices, loops );
	}

	Mesh SampleMesh::Disc( BuildFunc func, float inner, float outer, int slices, int loops )
	{
		Renderer::Disc quadric( inner, outer );
		return func( quadric, slices, loops );
	}

	Mesh SampleMesh::SolidPartialDisc( float inner, float outer, int slices, int loops, Degree start, Degree sweep )
	{
		return PartialDisc( IQuadric::Solid, inner, outer, slices, loops, start, sweep );
	}

	Mesh SampleMesh::WirePartialDisc( float inner, float outer, int slices, int loops, Degree start, Degree sweep )
	{
		return PartialDisc( IQuadric::Wire, inner, outer, slices, loops, start, sweep );
	}
	
	Mesh SampleMesh::PartialDisc( BuildFunc func, float inner, float outer, int slices, int loops, Radian start, Radian sweep )
	{
		Renderer::Disc quadric( inner, outer, start, sweep );
		return func( quadric, slices, loops );
	}
	
}