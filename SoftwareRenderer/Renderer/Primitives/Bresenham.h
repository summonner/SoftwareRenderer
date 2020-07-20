#pragma once
#include "Math/Vector2.hpp"

namespace Renderer
{
	class Vertex;
	class Bresenham final
	{
	public:
		Bresenham( const Vertex& a, const Vertex& b );
		Bresenham( const Vertex* a, const Vertex* b );
		~Bresenham();

		bool Next();
		Vector4 GetColor() const;
		float GetDepth() const;

	private:
		float CalculateTx() const;
		float CalculateTy() const;

	private:
		const Vertex& a;
		const Vertex& b;
		const Vector2Int diff;
		const Vector2Int sign;
		int d;

		const std::function<float(const Bresenham&)> CalculateT;

	public:
		Vector2Int p;
		float t;
	};
}