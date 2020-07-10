#pragma once
#include "Math/Vector2Int.h"
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

	private:
		Vector2Int current;
		const int width;
		const int height;
	};
}