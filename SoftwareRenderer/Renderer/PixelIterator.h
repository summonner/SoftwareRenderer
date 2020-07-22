#pragma once
#include "Math/Vector2.hpp"
#include "Util/IBaseIterator.h"

namespace Renderer
{
	class PixelIterator final : public IBaseIterator<PixelIterator, Vector2Int>
	{
	public:
		PixelIterator( int width, int height, int x, int y );

		bool operator !=( const PixelIterator& other ) const override;
		const PixelIterator& operator ++() override;
		Vector2Int operator *() const override;

		inline static PixelIterator begin( int width, int height )
		{
			return PixelIterator( width, height, 0, 0 );
		}

		inline static PixelIterator end( int width, int height )
		{
			return PixelIterator( width, height, width - 1, height - 1 );
		}

	private:
		Vector2Int current;
		const int width;
		const int height;
	};
}