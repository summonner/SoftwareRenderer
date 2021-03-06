#include "framework.h"
#include "BresenhamList.h"
#include "../PixelValues.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	BresenhamList::BresenhamList( const std::vector<const Vertex*>& vertices, ShadeModel::ShadeFunc shadeFunc, bool smooth )
		: currentIndex( 0 )
		, _x( 0 )
		, x( _x )
	{
		edges.reserve( vertices.size() - 1 );
		const Vertex* a = nullptr;
		for ( const auto b : vertices )
		{
			if ( a != nullptr )
			{
				if ( smooth )
				{
					edges.emplace_back( a->screen * 2, b->screen * 2 , VertexInterpolator( *a, *b, shadeFunc ) );
				}
				else
				{
					edges.emplace_back( *a, *b, shadeFunc );
				}
			}

			a = b;
		}
	}

	BresenhamList::BresenhamList( const BresenhamList& source )
		: currentIndex( source.currentIndex )
		, edges( source.edges )
		, _x( source.x )
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
			return NextY( y );
		}

		_x = GetCurrent().p.x;
		return true;
	}

	PixelValues BresenhamList::GetValues() const
	{
		const auto& e = GetCurrent();
		return e.GetValues();
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