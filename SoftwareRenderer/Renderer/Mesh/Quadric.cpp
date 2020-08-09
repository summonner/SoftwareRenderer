#include "framework.h"
#include "Quadric.h"
#include "Mesh.h"
#include "Math/Vector3.hpp"
#include "Renderer/Vertex.h"

namespace Renderer
{
	void Quadric::Circle( float tStacks, int slices, bool useTexture, char normalDirection, std::vector<Vertex>& vertices ) const
	{
		const float radius = Radius( tStacks );
		const float z = Height( tStacks );
		for ( auto i = 0; i <= slices; ++i )
		{
			const auto tSlices = (float)i / slices;
			const auto theta = Theta( tSlices );
			const auto x = sin( theta ) * radius;
			const auto y = cos( theta ) * radius;
			Vertex vertex;
			vertex.position = Vector4( x, y, z, 1 );
			if ( useTexture == true )
			{
				vertex.texcoord = Texcoord( tSlices, tStacks );
			}
			if ( normalDirection != 0 )
			{
				vertex.normal = Normal( vertex.position ) * normalDirection;
			}
			vertices.push_back( vertex );
		}
	}

	std::vector<Vertex> Quadric::Vertices( int slices, int stacks, bool useTexture, char normalDirection ) const
	{
		std::vector<Vertex> vertices;
		vertices.reserve( (slices + 1) * (stacks + 1) );

		for ( auto i = 0; i <= stacks; ++i )
		{
			const auto t = (float)i / stacks;
			Circle( t, slices, useTexture, normalDirection, vertices );
		}
		return vertices;
	}

	std::pair<Mesh::DrawMode, std::vector<Mesh::IndexType>> Quadric::Solid( int slices, int stacks )
	{
		std::vector<Mesh::IndexType> indices;
		indices.reserve( slices * stacks * 4 );

		for ( auto i = 1; i <= stacks; ++i )
		{
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
		return { Mesh::DrawMode::Quads, indices };
	}

	std::pair<Mesh::DrawMode, std::vector<Mesh::IndexType>> Quadric::Wire( int slices, int stacks )
	{
		std::vector<Mesh::IndexType> indices;
		indices.reserve( slices * (stacks * 2 + 1) * 2 );

		for ( auto j = 0; j < slices; ++j )
		{
			const auto current = j;
			indices.emplace_back( current );
			indices.emplace_back( current + 1 );
		}

		for ( auto i = 1; i <= stacks; ++i )
		{
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

		return { Mesh::DrawMode::Lines, indices };
	}
	Mesh Quadric::Build( IndexFunc func, int slices, int stacks ) const
	{
		return Build( func, slices, stacks, true, 1 );
	}

	Mesh Quadric::Build( IndexFunc func, int slices, int stacks, bool useTexture, char normalDirection ) const
	{
		auto vertices = Quadric::Vertices( slices, stacks, useTexture, normalDirection );
		if ( func != nullptr )
		{
			auto indices = func( slices, stacks );
			return Mesh( indices.first, std::move( vertices ), std::move( indices.second ) );
		}
		else
		{
			return Mesh( DrawMode::Points, std::move( vertices ) );
		}
	}
}