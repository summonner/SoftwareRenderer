#include "framework.h"
#include "Quadric.h"
#include "Mesh.h"
#include "Math/Vector3.hpp"
#include "Renderer/Vertex.h"

namespace Renderer
{
	Quadric::Quadric()
		: useTexture( true )
		, normalDirection( 1 )
		, color( 1, 1, 1, 1 )
	{
	}

	void Quadric::Circle( float tStacks, int slices, std::vector<Vertex>& vertices ) const
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
			vertex.color = color;
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

	std::vector<Vertex> Quadric::Vertices( int slices, int stacks ) const
	{
		std::vector<Vertex> vertices;
		vertices.reserve( (slices + 1) * (stacks + 1) );

		for ( auto i = 0; i <= stacks; ++i )
		{
			const auto t = (float)i / (float)stacks;
			Circle( t, slices, vertices );
		}
		return vertices;
	}

	std::pair<Mesh::DrawMode, std::vector<Mesh::IndexType>> Quadric::Solid( int slices, int stacks ) const
	{
		std::vector<Mesh::IndexType> indices;
		indices.reserve( slices * stacks * 4 );

		auto prevRadius = Radius( 0 );
		for ( auto i = 1; i <= stacks; ++i )
		{
			const auto currentRadius = Radius( (float)i / (float)stacks );
			for ( auto j = 0; j < slices; ++j )
			{
				const auto current = j + i * (slices + 1);
				const auto prev = current - (slices + 1);
				if ( prevRadius > FLT_EPSILON )
				{
					indices.emplace_back( prev );
					indices.emplace_back( prev + 1 );
					indices.emplace_back( current + 1 );
				}

				if ( currentRadius > FLT_EPSILON )
				{
					indices.emplace_back( prev );
					indices.emplace_back( current + 1 );
					indices.emplace_back( current );
				}
			}
			prevRadius = currentRadius;
		}

		return { Mesh::DrawMode::Triangles, indices };
	}

	std::pair<Mesh::DrawMode, std::vector<Mesh::IndexType>> Quadric::Wire( int slices, int stacks ) const
	{
		std::vector<Mesh::IndexType> indices;
		indices.reserve( slices * (stacks * 2 + 1) * 2 );

		auto currentRadius = Radius( 0 );
		if ( currentRadius > FLT_EPSILON )
		{
			for ( auto j = 0; j < slices; ++j )
			{
				const auto current = j;
				indices.emplace_back( current );
				indices.emplace_back( current + 1 );
			}
		}

		for ( auto i = 1; i <= stacks; ++i )
		{
			currentRadius = Radius( (float)i / (float)stacks );
			for ( auto j = 0; j < slices; ++j )
			{
				const auto current = j + i * (slices + 1);
				const auto prev = current - (slices + 1);

				if ( currentRadius > FLT_EPSILON )
				{
					indices.emplace_back( current );
					indices.emplace_back( current + 1 );
				}

				indices.emplace_back( prev );
				indices.emplace_back( current );
			}
		}

		return { Mesh::DrawMode::Lines, indices };
	}

	Mesh Quadric::Build( IndexFunc func, int slices, int stacks ) const
	{
		auto vertices = Quadric::Vertices( slices, stacks );
		if ( func != nullptr )
		{
			auto indices = (this->*func)( slices, stacks );
			return Mesh( indices.first, std::move( vertices ), std::move( indices.second ) );
		}
		else
		{
			return Mesh( DrawMode::Points, std::move( vertices ) );
		}
	}
}