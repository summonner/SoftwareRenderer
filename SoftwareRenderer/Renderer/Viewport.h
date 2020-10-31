#pragma once
#include "Math/Bounds.h"
#include "ScissorBox.h"

class Matrix4x4;
namespace Renderer
{
	class Viewport final
	{
	public:
		Viewport( const Bounds& max );
		~Viewport();

		void Set( int left, int bottom, int width, int height );
		Bounds GetBounds() const;
		void Reset();

		operator Matrix4x4() const;

		ScissorBox scissor;
	private:
		Bounds bounds;
		Bounds max;
	};
}