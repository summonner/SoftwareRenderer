#include "framework.h"
#include "SampleMesh.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Disc.h"

namespace Renderer
{
	Mesh SampleMesh::SolidCylinder( float base, float top, float height, int slices, int stacks )
	{
		return Cylinder( base, top, height ).Build( Quadric::Solid, slices, stacks );
	}

	Mesh SampleMesh::WireCylinder( float base, float top, float height, int slices, int stacks )
	{
		return Cylinder( base, top, height ).Build( Quadric::Wire, slices, stacks );
	}


	Mesh SampleMesh::SolidSphere( float radius, int slices, int stacks )
	{
		return Sphere( radius ).Build( Quadric::Solid, slices, stacks );
	}

	Mesh SampleMesh::WireSphere( float radius, int slices, int stacks )
	{
		return Sphere( radius ).Build( Quadric::Wire, slices, stacks );
	}


	Mesh SampleMesh::SolidDisc( float inner, float outer, int slices, int loops )
	{
		return Disc( inner, outer ).Build( Quadric::Solid, slices, loops );
	}

	Mesh SampleMesh::WireDisc( float inner, float outer, int slices, int loops )
	{
		return Disc( inner, outer ).Build( Quadric::Wire, slices, loops );
	}


	Mesh SampleMesh::SolidPartialDisc( float inner, float outer, int slices, int loops, Degree start, Degree sweep )
	{
		return Disc( inner, outer ).Build( Quadric::Solid, slices, loops );
	}

	Mesh SampleMesh::WirePartialDisc( float inner, float outer, int slices, int loops, Degree start, Degree sweep )
	{
		return Disc( inner, outer ).Build( Quadric::Wire, slices, loops );
	}
}