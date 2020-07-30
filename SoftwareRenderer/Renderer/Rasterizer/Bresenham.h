#pragma once
#include "Math/Vector2.hpp"

namespace Renderer
{
	class Vertex;
	struct PixelValues;
	class Bresenham final
	{
	public:
		Bresenham( const Vertex& a, const Vertex& b );
		Bresenham( const Vertex* a, const Vertex* b );
		Bresenham( const Bresenham& source );
		~Bresenham();

		bool Next();
		bool NextY( const int y );
		Vector4 GetColor() const;
		float GetDepth() const;
		Vector2 GetTexcoord() const;
		PixelValues GetValues() const;

	private:
		void MoveNext();
		void CalculateParams();
		float CalculateTx() const;
		float CalculateTy() const;

	private:
		const Vertex& a;
		const Vertex& b;
		const Vector2Int diff;
		const Vector2Int sign;
		int d;

		const std::function<float(const Bresenham&)> CalculateT;

		Vector2Int _p;
		float _w;
		float t;

	public:
		const Vector2Int& p;
		const float& w;
	};
}