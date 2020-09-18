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

	CullFaceComponent::Result CullFaceComponent::Apply( float facet ) const
	{
		if ( enabled == true )
		{
			if ( cullFace == Cull::FrontAndBack )
			{
				return Result::Cull;
			}

			facet *= (int)frontFace;
			if ( facet * (int)cullFace < 0 )
			{
				return Result::Cull;
			}
		}

		if ( facet >= 0 )
		{
			return Result::Front;
		}
		else
		{
			return Result::Back;
		}
	}
}