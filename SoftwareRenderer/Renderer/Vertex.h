#pragma once
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

class Matrix4x4;
namespace Renderer
{
	class Vertex final
	{
	public:
		Vertex();
		Vertex( const Vertex& left, const Vertex& right, const float t );
		~Vertex();

		void Process( const Matrix4x4& projection );
		void PerspectiveDivide( const Matrix4x4& viewport );
		static Vertex Lerp( const Vertex& left, const Vertex& right, const float t );

	public:
		Vector4 position;
		Vector4 color;
		Vector2 texcoord;
		Vector3 normal;

		Vector2Int screen;
	};
}