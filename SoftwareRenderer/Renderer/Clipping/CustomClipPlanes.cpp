#include "framework.h"
#include "CustomClipPlanes.h"
#include "Renderer/Vertex.h"
#include "PlaneIterator.h"

namespace Renderer
{
	CustomClipPlanes::CustomClipPlanes()
	{
	}

	CustomClipPlanes::~CustomClipPlanes()
	{
	}

	void CustomClipPlanes::Add( const Vector4* coefficients )
	{
		if ( const auto found = std::find( planes.begin(), planes.end(), coefficients ); found != planes.end() )
		{
			return;
		}

		planes.emplace_back( coefficients );
	}

	void CustomClipPlanes::Remove( const Vector4* coefficients )
	{
		if ( const auto found = std::find( planes.begin(), planes.end(), coefficients ); found != planes.end() )
		{
			planes.erase( found );
		}
	}

	CustomClipPlanes::operator const PlaneIterator() const
	{
		return PlaneIterator( planes, 0 );
	}
}