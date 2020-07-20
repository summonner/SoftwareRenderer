#pragma once
#include "IRasterizer.h"

namespace Renderer
{
	class Vertex;
	class Point final : public IRasterizer
	{
	public:
		Point( const Vertex& v );
		~Point() override;
	};
}