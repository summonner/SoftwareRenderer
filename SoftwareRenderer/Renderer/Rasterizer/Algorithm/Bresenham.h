#pragma once
#include "Math/Vector2.hpp"
#include "../ShadeModel.h"
#include "VertexInterpolator.h"

namespace Renderer
{
	class Vertex;
	struct PixelValues;
	class Bresenham final
	{
	public:
		Bresenham( const Vertex& a, const Vertex& b, ShadeModel::ShadeFunc shadeFunc );
		Bresenham( const Vector2Int& a, const Vector2Int& b, const VertexInterpolator& values );
		Bresenham( const Bresenham& source );
		~Bresenham();

		bool Next();
		bool NextY( const int y );
		PixelValues GetValues() const;
		bool IsXMajor() const;

	private:
		void MoveNext();
		void CalculateParams();
		float CalculateTx() const;
		float CalculateTy() const;

	private:
		const Vector2Int a;
		const Vector2Int b;
		const Vector2Int diff;
		const Vector2Int next;
		int d;

		const ShadeModel::ShadeFunc shadeFunc;
		const std::function<float(const Bresenham&)> CalculateT;
		const VertexInterpolator values;

		Vector2Int _p;
		float t;

	public:
		const Vector2Int& p;
	};
}