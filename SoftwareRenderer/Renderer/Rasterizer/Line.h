#pragma once
#include "IRasterizer.h"

namespace Renderer
{
	class Vertex;
	class Line final : public IRasterizer
	{
	public:
		Line( const Vertex& a, const Vertex& b );
		~Line() override;
	};
}