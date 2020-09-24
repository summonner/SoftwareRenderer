#pragma once
#include "Math/Vector4.hpp"
#include "Math/Vector2.hpp"

namespace Renderer
{
	struct PixelValues final
	{
		float w;
		float depth;
		Vector4 color;
		Vector2 texcoord;
	};
}