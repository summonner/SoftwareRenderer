#pragma once
#include "Bresenham.h"

namespace Renderer
{
	struct PixelValues;
	class BresenhamList final
	{
	public:
		BresenhamList( std::initializer_list<const Vertex*> vertices );
		BresenhamList( const BresenhamList& source );
		~BresenhamList();

		bool NextY( int y );
		PixelValues GetValues() const;
		const Bresenham& GetCurrent() const;

	public:
		const int& x;

	private:
		int _x;
		int currentIndex;
		std::vector<Bresenham> edges;
	};
}