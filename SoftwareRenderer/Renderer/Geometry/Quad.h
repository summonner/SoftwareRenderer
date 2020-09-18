#pragma once
#include "IGeometry.h"

namespace Renderer
{
	class Vertex;
	class Quad final : public IGeometry
	{
	public:
		Quad( const Vertex& a, const Vertex& b, const Vertex& c, const Vertex& d );
		~Quad() override;

		std::unique_ptr<IRasterizer> Clip( const Matrix4x4& viewport, const PlaneIterator& planes ) const override;

	private:
		const Vertex& a;
		const Vertex& b;
		const Vertex& c;
		const Vertex& d;
	};
}