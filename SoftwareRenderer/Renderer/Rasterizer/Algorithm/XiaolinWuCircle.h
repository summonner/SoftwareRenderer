#pragma once
#include "Math/Vector2.hpp"

namespace Renderer
{
	class XiaolinWuCircle
	{
	public:
		XiaolinWuCircle( float radius );
		~XiaolinWuCircle();

		bool Next();
		bool IsXMajor() const;

	private:
		const float rr;
		Vector2 _p;
		int m;
		const static float invSqrt2;

	public:
		const Vector2& p;
	};
}