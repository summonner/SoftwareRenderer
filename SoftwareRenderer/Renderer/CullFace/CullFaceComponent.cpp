#include "framework.h"
#include "CullFaceComponent.h"
#include "Math/Vector2.hpp"
#include "Renderer/Rasterizer/IRasterizer.h"

namespace Renderer
{
	CullFaceComponent::CullFaceComponent()
		: cullFace( Cull::Back )
		, frontFace( Front::CCW )
	{
	}

	CullFaceComponent::~CullFaceComponent()
	{
	}

	void CullFaceComponent::Reset()
	{
		BaseComponent::Reset();
		cullFace = Cull::Back;
		frontFace = Front::CCW;
	}

	void CullFaceComponent::SetCullFace( Cull cullFace )
	{
		this->cullFace = cullFace;
	}

	void CullFaceComponent::SetFrontFace( Front frontFace )
	{
		this->frontFace = frontFace;
	}

	bool CullFaceComponent::Apply( const Vector2Int& a, const Vector2Int& b, const Vector2Int& c ) const
	{
		const auto ab = b - a;
		const auto ac = c - a;
		const auto facet = ab.Area( ac );
		return Apply( facet );
	}

	bool CullFaceComponent::Apply( const float facet ) const
	{
		if ( cullFace == Cull::FrontAndBack )
		{
			return false;
		}
		else
		{
			return facet * (int)cullFace * (int)frontFace >= 0;
		}
	}

	bool CullFaceComponent::Apply( const IRasterizer& rasterizer ) const
	{
		if ( enabled == false )
		{
			return true;
		}

		return Apply( rasterizer.CheckFacet() );
	}
}