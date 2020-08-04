#pragma once
#include "Renderer/IComponent.h"

namespace Renderer
{
	class CullFaceComponent final : public BaseComponent
	{
	public:
		enum class Cull
		{
			Back = 1,
			Front = -1,
			FrontAndBack = 0,
		};

		enum class Front
		{
			CW = -1,
			CCW = 1,
		};

	public:
		CullFaceComponent();
		~CullFaceComponent();

		void SetCullFace( const Cull cullFace );
		void SetFrontFace( const Front frontFace );

		std::function<bool( const Vector2Int&, const Vector2Int&, const Vector2Int& )> AsFunc() const;

		bool Apply( const Vector2Int& a, const Vector2Int& b, const Vector2Int& c ) const;
		bool Apply( const float facet ) const;

	private:
		Cull cullFace;
		Front frontFace;
	};
}

using CullFace = Renderer::CullFaceComponent::Cull;
using FrontFace = Renderer::CullFaceComponent::Front;