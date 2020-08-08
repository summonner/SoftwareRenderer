#include "framework.h"
#include "SampleMesh.h"
#include "Mesh.h"
#include "Math/Radian.h"

namespace Renderer
{
	Mesh SampleMesh::SolidCylinder( float base, float top, float height, int slices, int stacks )
	{
		std::vector<Vertex> vertices;
		std::vector<Mesh::IndexType> indices;

		vertices.reserve( (slices + 1) * stacks );
		indices.reserve( slices * (stacks - 1) * 4 );

		Circle( 0.f, 0.f, base, slices, vertices );
		for ( auto i = 1; i <= stacks; ++i )
		{
			const auto t = (float)i / stacks;
			Circle( height * t, t, ::Lerp( base, top, t ), slices, vertices );

			for ( auto j = 0; j < slices; ++j )
			{
				const auto current = j + i * (slices + 1);
				const auto prev = current - (slices + 1);
				indices.emplace_back( prev );
				indices.emplace_back( prev + 1 );
				indices.emplace_back( current + 1 );
				indices.emplace_back( current );
			}
		}

		return Mesh( DrawMode::Quads, std::move( vertices ), std::move( indices ) );
	}

	Mesh SampleMesh::WireCylinder( float base, float top, float height, int slices, int stacks )
	{
		std::vector<Vertex> vertices;
		std::vector<Mesh::IndexType> indices;

		vertices.reserve( (slices + 1) * stacks );
		indices.reserve( slices * (stacks * 2 - 1) * 2 );

		Circle( 0.f, 0.f, base, slices, vertices );
		for ( auto j = 0; j < slices; ++j )
		{
			const auto current = j;
			indices.emplace_back( current );
			indices.emplace_back( current + 1 );
		}

		for ( auto i = 1; i <= stacks; ++i )
		{
			const auto t = (float)i / stacks;
			Circle( height * t, t, ::Lerp( base, top, t ), slices, vertices );

			for ( auto j = 0; j < slices; ++j )
			{
				const auto current = j + i * (slices + 1);
				const auto prev = current - (slices + 1);
				indices.emplace_back( current );
				indices.emplace_back( current + 1 );

				indices.emplace_back( prev );
				indices.emplace_back( current );
			}
		}

		return Mesh( DrawMode::Lines, std::move( vertices ), std::move( indices ) );
	}

	void SampleMesh::Circle( float z, float v, float radius, int slices, std::vector<Vertex>& vertices )
	{
		for ( auto i = 0; i <= slices; ++i )
		{
			const auto t = (float)i / slices;
			const auto theta = Radian( 2 * PI * t );
			const auto x = sin( theta );
			const auto y = cos( theta );
			Vertex vertex;
			vertex.position = Vector4( x, y, z, 1 );
			vertex.texcoord = Vector2( t, v );
			vertex.normal = Vector3( vertex.position ) - Vector3( 0, 0, z );
			vertices.push_back( vertex );
		}
	}
}