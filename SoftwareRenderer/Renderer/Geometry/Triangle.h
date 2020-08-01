#pragma once
#include "IGeometry.h"

namespace Renderer
{
	class Vertex;
	class DerivativeTexcoord;
	class Triangle final : public IGeometry
	{
	public:
		Triangle( const Vertex& a, const Vertex& b, const Vertex& c );
		~Triangle() override;

		std::unique_ptr<IRasterizer> Clip() const override;
	private:
		DerivativeTexcoord Derivative() const;

	private:
		const Vertex& a;
		const Vertex& b;
		const Vertex& c;
	};
}