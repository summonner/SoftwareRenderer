#pragma once
#include "Bresenham.h"

namespace Renderer
{
	struct PixelValues;
	class BresenhamList final
	{
	public:
		BresenhamList( const std::vector<const Vertex*>& vertices, ShadeModel::ShadeFunc shadeFunc, bool smooth );
		BresenhamList( const BresenhamList& source );
		~BresenhamList();

		bool NextY( int y );
		PixelValues GetValues() const;
		const Bresenham& GetCurrent() const;

	public:
		const int& x;

	private:
		int _x;
		size_t currentIndex;
		std::vector<Bresenham> edges;
	};
}