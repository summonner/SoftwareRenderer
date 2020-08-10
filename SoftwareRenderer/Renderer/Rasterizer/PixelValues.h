#pragma once
#include "Math/Vector4.hpp"
#include "Math/Vector2.hpp"

namespace Renderer
{
	struct PixelValues final
	{
		const float w;
		const float depth;
		const Vector4 color;
		const Vector2 texcoord;
	};
}