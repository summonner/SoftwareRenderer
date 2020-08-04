#pragma once
#include "IRasterizer.h"

namespace Renderer
{
	class Vertex;
	class CommonRasterizer abstract : public IRasterizer
	{
	public:
		CommonRasterizer( std::vector<Vertex>&& vertices );
		virtual ~CommonRasterizer() override;

		bool PerspectiveDivide( const Matrix4x4& viewport ) override;

	protected:
		virtual bool PostPerspectiveDivide() abstract;

	protected:
		std::vector<Vertex> vertices;
	};
}