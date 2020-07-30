#include "framework.h"
#include "PixelValues.h"

namespace Renderer
{
	PixelValues PixelValues::Lerp( const PixelValues& left, const PixelValues& right, const float t )
	{
		return PixelValues {
			::Lerp( left.w, right.w, t ),
			::Lerp( left.depth, right.depth, t ),
			Vector4::Lerp( left.color, right.color, t ),
			Vector2::Lerp( left.texcoord, right.texcoord, t )
		};
	}
}