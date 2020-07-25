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
		~Vertex();

		void Process( const Matrix4x4& projection, const Matrix4x4& viewport );

	public:
		Vector4 position;
		Vector4 color;
		Vector2 texcoord;

		Vector2Int screen;
	};

}