#include "framework.h"
#include "ScissorBox.h"

namespace Renderer
{
	ScissorBox::ScissorBox( const Bounds& max )
		: bounds( max )
	{
	}

	ScissorBox::~ScissorBox()
	{
	}

	void ScissorBox::Set( int left, int bottom, int width, int height )
	{
		bounds = Bounds( RangeInt( left, left + width ), RangeInt( bottom, bottom + height ) );
	}

	Bounds ScissorBox::Get() const
	{
		return bounds;
	}

	Bounds ScissorBox::Clamp( const Bounds& viewport ) const
	{
		const auto x = viewport.x.Clamp( bounds.x );
		const auto y = viewport.y.Clamp( bounds.y );
		return Bounds( x, y );
	}
}