#pragma once
#include "IGeometry.h"

namespace Renderer
{
	class Vertex;
	class DerivativeTexcoord;
	class Line final : public IGeometry
	{
	public:
		Line( const Vertex& a, const Vertex& b );
		~Line() override;

		std::unique_ptr<IRasterizer> Clip() const;

	private:
		DerivativeTexcoord Derivative() const;

	private:
		const Vertex& a;
		const Vertex& b;
	};
}