#include "framework.h"
#include "Viewport.h"
#include "Math/Matrix4x4.h"

namespace Renderer
{
	Viewport::Viewport( const Bounds& max )
		: bounds( max )
		, scissor( max )
		, max( max )
	{
	}

	Viewport::~Viewport()
	{
	}

	void Viewport::Set( int left, int bottom, int width, int height )
	{
		const auto x = max.x.Clamp( left, left + width );
		const auto y = max.y.Clamp( bottom, bottom + height );
		bounds = Bounds( x, y );
	}

	void Viewport::Reset()
	{
		bounds = max;
	}

	Viewport::operator Matrix4x4() const
	{
		const auto w = bounds.x.Length() * 0.5f;
		const auto h = bounds.y.Length() * 0.5f;
		const auto x = w + bounds.x.min + 0.5f;
		const auto y = h + bounds.y.min + 0.5f;

		return Matrix4x4(
			w, 0, 0, x,
			0, h, 0, y,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	Bounds Viewport::GetBounds() const
	{
		if ( scissor.IsEnable() == true )
		{
			return scissor.Clamp( bounds );
		}
		else
		{
			return bounds;
		}
	}
}