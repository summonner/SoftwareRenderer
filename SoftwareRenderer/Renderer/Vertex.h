#pragma once
#include "Math/Vector2.hpp"
#include "Math/Vector4.hpp"

class Matrix4x4;
namespace Renderer
{
	class Vertex final
	{
	public:
		Vertex();
		~Vertex();

		void Rasterize( const Matrix4x4& view );

	public:
		Vector4 position;
		Vector4 color;
		Vector2 screenCoordinate;
		float depth;
	};

}