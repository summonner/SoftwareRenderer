#pragma once
#include "Renderer/Vertex.h"
#include "Math/Vector2.hpp"
#include "../ShadeModel.h"
#include "VertexInterpolator.h"

namespace Renderer
{
	struct PixelValues;
	class XiaolinWu final
	{
	public:
		XiaolinWu( const Vertex& a, const Vertex& b, const ShadeModel::ShadeFunc shadeFunc );
		~XiaolinWu();

		bool Next();
		PixelValues GetValues() const;
		bool IsXMajor() const;

	private:
		const VertexInterpolator values;
		const Vector2 a;
		const Vector2 b;
		const Vector2 diff;
		const bool isXMajor;
		const float slope;
		const int next;

		Vector2 _p;
		float t;

	public:
		const Vector2& p;
	};
}