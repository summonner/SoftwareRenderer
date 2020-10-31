#pragma once
#include "IComponent.h"
#include "Math/Bounds.h"

namespace Renderer
{
	class ScissorBox final : public BaseComponent
	{
	public:
		ScissorBox( const Bounds& bounds );
		~ScissorBox();

		void Set( int left, int bottom, int width, int height );
		Bounds Get() const;
		Bounds Clamp( const Bounds& bounds ) const;

	private:
		Bounds bounds;
	};
}