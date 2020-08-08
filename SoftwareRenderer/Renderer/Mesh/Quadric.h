#pragma once

namespace Renderer
{
	class Mesh;
	class Vertex;
	class IQuadric abstract
	{
	public:
		virtual ~IQuadric() {};

		virtual float Radius( float t ) const abstract;
		virtual float Height( float t ) const abstract;
		virtual Vector3 Normal( const Vector3& position ) const abstract;
		virtual Radian Theta( float t ) const { return 2 * PI * t; };

		static void Circle( const IQuadric& quadric, float t, int slices, std::vector<Vertex>& vertices );
		static Mesh Solid( const IQuadric& quadric, int slices, int stacks );
		static Mesh Wire( const IQuadric& quadric, int slices, int stacks );
	};

	class Cylinder final : public IQuadric
	{
	public:
		Cylinder( float base, float top, float radius );
		~Cylinder() override;

		float Radius( float t ) const override;
		float Height( float t ) const override;
		Vector3 Normal( const Vector3& position ) const override;

	private:
		const float base;
		const float top;
		const float height;
	};

	class Sphere final : public IQuadric
	{
	public:
		Sphere( float radius );
		~Sphere() override;

		float Radius( float t ) const override;
		float Height( float t ) const override;
		Vector3 Normal( const Vector3& position ) const override;

	private:
		const float radius;
	};

	class Disc final : public IQuadric
	{
	public:
		Disc( float inner, float outer );
		Disc( float inner, float outer, Radian start, Radian sweep );
		~Disc() override;

		float Radius( float t ) const override;
		float Height( float t ) const override;
		Vector3 Normal( const Vector3& position ) const override;
		Radian Theta( float t ) const override;

	private:
		const float inner;
		const float outer;
		const Radian start;
		const Radian sweep;
	};
}