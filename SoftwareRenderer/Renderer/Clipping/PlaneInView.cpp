#include "framework.h"
#include "PlaneInView.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	PlaneInView::PlaneInView( const Vector4* coefficients )
		: coefficients( coefficients )
	{
	}

	PlaneInView::~PlaneInView()
	{
	}

	bool PlaneInView::operator ==( const Vector4* other ) const
	{
		return coefficients == other;
	}

	float PlaneInView::Dot( const Vertex& vertex ) const
	{
		return coefficients->Dot( vertex.view );
	}

	float PlaneInView::DotWithDiff( const Vertex& v1, const Vertex& v2 ) const
	{
		const auto diff = v1.view - v2.view;
		return coefficients->Dot( diff );
	}
}