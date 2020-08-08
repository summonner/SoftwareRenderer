#include "framework.h"
#include "Quadric.h"
#include "Mesh.h"
#include "Math/Vector3.hpp"
#include "Renderer/Vertex.h"

namespace Renderer
{
	void IQuadric::Circle( const IQuadric& quadric, float v, int slices, std::vector<Vertex>& vertices )
	{
		const float radius = quadric.Radius( v );
		const float z = quadric.Height( v );
		for ( auto i = 0; i <= slices; ++i )
		{
			const auto u = (float)i / slices;
			const auto theta = quadric.Theta( u );
			const auto x = sin( theta ) * radius;
			const auto y = cos( theta ) * radius;
			Vertex vertex;
			vertex.position = Vector4( x, y, z, 1 );
			vertex.texcoord = Vector2( u, v );
			vertex.normal = quadric.Normal( vertex.position );
			vertices.push_back( vertex );
		}
	}

	Mesh IQuadric::Solid( const IQuadric& quadric, int slices, int stacks )
	{
		std::vector<Vertex> vertices;
		std::vector<Mesh::IndexType> indices;

		vertices.reserve( (slices + 1) * (stacks + 1) );
		indices.reserve( slices * (stacks * 2 + 1) * 2 );

		auto t = 0.f;
		Circle( quadric, t, slices, vertices );
		for ( auto i = 1; i <= stacks; ++i )
		{
			t = (float)i / stacks;
			Circle( quadric, t, slices, vertices );

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

	Mesh IQuadric::Wire( const IQuadric& quadric, int slices, int stacks )
	{
		std::vector<Vertex> vertices;
		std::vector<Mesh::IndexType> indices;

		vertices.reserve( (slices + 1) * (stacks + 1) );
		indices.reserve( slices * (stacks * 2 + 1) * 2 );

		auto t = 0.f;
		Circle( quadric, t, slices, vertices );
		for ( auto j = 0; j < slices; ++j )
		{
			const auto current = j;
			indices.emplace_back( current );
			indices.emplace_back( current + 1 );
		}

		for ( auto i = 1; i <= stacks; ++i )
		{
			t = (float)i / stacks;
			Circle( quadric, t, slices, vertices );

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


	Cylinder::Cylinder( float base, float top, float height )
		: base( base )
		, top( top )
		, height( height )
	{
	}

	Cylinder::~Cylinder()
	{
	}

	float Cylinder::Radius( float t ) const
	{
		return Lerp( base, top, t );
	}

	float Cylinder::Height( float t ) const
	{
		return height * t;
	}

	Vector3 Cylinder::Normal( const Vector3& position ) const
	{
		return Vector3( position.x, position.y, 0.f );
	}



	Sphere::Sphere( float radius )
		: radius( radius )
	{
	}

	Sphere::~Sphere()
	{
	}

	float Sphere::Radius( float t ) const
	{
		return sin( t * PI );
	}

	float Sphere::Height( float t ) const
	{
		return cos( t * PI );
	}

	Vector3 Sphere::Normal( const Vector3& position ) const
	{
		return position;
	}



	Disc::Disc( float inner, float outer )
		: inner( inner )
		, outer( outer )
		, start( 0.0f )
		, sweep( 2 * PI )
	{
	}

	Disc::Disc( float inner, float outer, Radian start, Radian sweep )
		: inner( inner )
		, outer( outer )
		, start( start )
		, sweep( sweep )
	{
	}

	Disc::~Disc()
	{
	}

	float Disc::Radius( float t ) const
	{
		return Lerp( inner, outer, t );
	}

	float Disc::Height( float t ) const
	{
		return 0.f;
	}

	Vector3 Disc::Normal( const Vector3& position ) const
	{
		return Vector3::up;
	}

	Radian Disc::Theta( float t ) const
	{
		return start + sweep * t;
	}
}