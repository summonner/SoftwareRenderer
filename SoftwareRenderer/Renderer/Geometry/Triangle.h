#pragma once
#include "IGeometry.h"

namespace Renderer
{
	class Vertex;
	class Triangle final : public IGeometry
	{
	public:
		Triangle( const Vertex& a, const Vertex& b, const Vertex& c );
		~Triangle() override;

		std::unique_ptr<IRasterizer> Clip( const Matrix4x4& viewport, const PlaneIterator& planes ) const override;


	private:
		const Vertex& a;
		const Vertex& b;
		const Vertex& c;
	};
}