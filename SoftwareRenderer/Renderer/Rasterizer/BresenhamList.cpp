#include "framework.h"
#include "BresenhamList.h"
#include "PixelValues.h"

namespace Renderer
{
	BresenhamList::BresenhamList( std::initializer_list<const Vertex*> vertices )
		: currentIndex( 0 )
		, x( _x )
	{
		edges.reserve( vertices.size() - 1 );
		const Vertex* a = nullptr;
		for ( const auto b : vertices )
		{
			if ( a != nullptr )
			{
				edges.emplace_back( *a, *b );
			}

			a = b;
		}
	}

	BresenhamList::BresenhamList( const BresenhamList& source )
		: currentIndex( source.currentIndex )
		, edges( source.edges )
		, x( _x )
	{
	}

	BresenhamList::~BresenhamList()
	{
	}

	bool BresenhamList::NextY( int y )
	{
		if ( currentIndex >= edges.size() )
		{
			return false;
		}

		if ( edges[currentIndex].NextY( y ) == false )
		{
			++currentIndex;
		}

		_x = GetCurrent().p.x;
		return true;
	}

	PixelValues BresenhamList::GetValues() const
	{
		const auto& e = GetCurrent();
		return PixelValues {
			e.w,
			e.GetDepth(),
			e.GetColor(),
			e.GetTexcoord()
		};
	}

	const Bresenham& BresenhamList::GetCurrent() const
	{
		assert( currentIndex >= 0 );
		if ( currentIndex < edges.size() )
		{
			return edges[currentIndex];
		}
		else
		{
			return edges[edges.size() - 1];
		}
	}
}