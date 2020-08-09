#pragma once
#include "Mesh.h"

namespace Renderer
{
	class Vertex;
	class Quadric abstract
	{
	public:
		virtual ~Quadric() {};

		virtual float Radius( float t ) const abstract;
		virtual float Height( float t ) const abstract;
		virtual Vector2 Texcoord( float tSlices, float tStacks ) const abstract;
		virtual Vector3 Normal( const Vector3& position ) const abstract;
		virtual Radian Theta( float t ) const { return 2 * PI * t; };

		static std::pair<Mesh::DrawMode, std::vector<Mesh::IndexType>> Solid( int slices, int stacks );
		static std::pair<Mesh::DrawMode, std::vector<Mesh::IndexType>> Wire( int slices, int stacks );

		using IndexFunc = std::function<std::pair<Mesh::DrawMode, std::vector<Mesh::IndexType>>( int, int )>;
		Mesh Build( IndexFunc indexFunc, int slices, int stacks ) const;
		Mesh Build( IndexFunc indexFunc, int slices, int stacks, bool useTexture, char normalDirection ) const;

	private:
		std::vector<Vertex> Vertices( int slices, int stacks, bool useTexture, char normalDirection ) const;
		void Circle( float t, int slices, bool useTexture, char normalDirection, std::vector<Vertex>& vertices ) const;
	};
}