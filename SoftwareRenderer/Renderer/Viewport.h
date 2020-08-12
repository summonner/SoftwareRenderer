#pragma once
#include "Math/Bounds.h"

class Matrix4x4;
namespace Renderer
{
	class Viewport final
	{
	public:
		Viewport( const Bounds& max );
		~Viewport();

		void Set( int left, int bottom, int width, int height );
		Bounds Get() const;
		void Reset();

		operator Matrix4x4() const;
		operator Bounds() const;

	private:
		Bounds bounds;
		const Bounds max;
	};
}