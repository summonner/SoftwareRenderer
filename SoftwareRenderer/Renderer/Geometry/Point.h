#pragma once
#include "IGeometry.h"

namespace Renderer
{
	class Vertex;
	class Point final : public IGeometry
	{
	public:
		Point( const Vertex& v );
		~Point() override;

		std::unique_ptr<IRasterizer> Clip( const Matrix4x4& viewport ) const override;

	private:
		const Vertex& v;
	};
}