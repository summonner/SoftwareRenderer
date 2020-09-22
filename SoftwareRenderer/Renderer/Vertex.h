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

		void PerspectiveDivide( const Matrix4x4& viewport );
		static Vertex Lerp( const Vertex& left, const Vertex& right, const float t );
		Vertex Offset( const Vector2& offset ) const;
		Vertex Offset( float x, float y ) const;

	public:
		Vector4 position;
		Vector4 color;
		Vector2 texcoord;
		Vector3 normal;

		Vector4 view;
		Vector2Int screen;
	};
}