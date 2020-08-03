#include "framework.h"
#include "CullFaceComponent.h"
#include "Math/Vector2.hpp"

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

	void CullFaceComponent::SetEnable( bool enable )
	{
		enabled = enable;
	}

	void CullFaceComponent::SetCullFace( Cull cullFace )
	{
		this->cullFace = cullFace;
	}

	void CullFaceComponent::SetFrontFace( Front frontFace )
	{
		this->frontFace = frontFace;
	}

	std::function<bool( const Vector2Int&, const Vector2Int&, const Vector2Int& )> CullFaceComponent::AsFunc() const
	{
		if ( enabled == false )
		{
			return nullptr;
		}

		const auto apply = static_cast<bool (CullFaceComponent::*)(const Vector2Int&, const Vector2Int&, const Vector2Int&) const>(&CullFaceComponent::Apply);
		return std::bind( apply, *this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 );
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
		return facet * (int)cullFace * (int)frontFace > 0;
	}
}