#include "framework.h"
#include "PlaneInClip.h"
#include "Renderer/Vertex.h"

namespace Renderer
{
	PlaneInClip::PlaneInClip( const Vector4& coefficients )
		: coefficients( coefficients )
	{
	}

	PlaneInClip::~PlaneInClip()
	{
	}

	float PlaneInClip::Dot( const Vertex& vertex ) const
	{
		return coefficients.Dot( vertex.position );
	}

	float PlaneInClip::DotWithDiff( const Vertex& v1, const Vertex& v2 ) const
	{
		const auto diff = v1.position - v2.position;
		return coefficients.Dot( diff );
	}
}