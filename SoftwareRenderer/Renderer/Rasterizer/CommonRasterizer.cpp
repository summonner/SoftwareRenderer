#include "framework.h"
#include "CommonRasterizer.h"
#include "DerivativeTexcoord.h"
#include "Renderer/Vertex.h"
#include "RasterizedPixel.h"

namespace Renderer
{
	CommonRasterizer::CommonRasterizer( std::vector<Vertex>&& vertices )
		: vertices( std::move( vertices ) )
	{
		assert( this->vertices.size() > 2 );
	}

	CommonRasterizer::~CommonRasterizer()
	{
	}

	bool CommonRasterizer::PerspectiveDivide( const Matrix4x4& viewport )
	{
		for ( auto& v : vertices )
		{
			v.PerspectiveDivide( viewport );
		}

		return PostPerspectiveDivide();
	}
}