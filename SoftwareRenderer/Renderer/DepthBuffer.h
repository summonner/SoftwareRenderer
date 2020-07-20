#pragma once
#include "Math/Vector.h"

namespace Renderer
{
	class DepthBuffer final
	{
	public:
		DepthBuffer( int width, int height );
		~DepthBuffer();

		void Clear();
		bool Test( const Vector2Int& coordinate, float depth );

	private:
		const int width;
		const int height;
		std::unique_ptr<float[]> pixels;
	};
}