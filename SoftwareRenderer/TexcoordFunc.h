#pragma once
#include "Math/Vector4.hpp"
#include "Renderer/IComponent.h"

class Matrix4x4;
namespace Renderer
{
	class Vertex;
	class Matrix;
	class TexcoordFunc final : public BaseComponent
	{
	public:
		enum class Type
		{
			EyeLinear,
			ObjectLinear,
			Sphere,
			Reflection,
		};

	public:
		TexcoordFunc( const Vector4& plane );
		~TexcoordFunc();

		void SetPlane( const Vector4& plane );
		void operator =( Type type );
		float operator ()( const Vertex& v, const Matrix& modelView ) const;

	private:
		using Func = std::function<float( const Vertex& v, const Matrix& modelView, const Vector4& plane )>;
		Func generateFunc;
		Vector4 plane;

	private:
		static const Dictionary<Type, Func> table;

		static float ObjectLinear( const Vertex& v, const Matrix& modelView, const Vector4& plane );
		static float EyeLinear( const Vertex& v, const Matrix& modelView, const Vector4& plane );
		static float Sphere( const Vertex& v, const Matrix& modelView, const Vector4& plane );
		static Vector3 Reflection( const Vertex& v );
		//static Matrix4x4 Reflection( const Vector3& normal );
	};
}
using TexcoordFunc = Renderer::TexcoordFunc::Type;