#pragma once
#include "Renderer/IComponent.h"

namespace Renderer
{
	class IRasterizer;
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

		enum class Result
		{
			Cull,
			Back,
			Front,
		};

	public:
		CullFaceComponent();
		~CullFaceComponent();

		void Reset() override;
		void SetCullFace( const Cull cullFace );
		void SetFrontFace( const Front frontFace );

		Result Apply( float facet ) const;

	private:
		Cull cullFace;
		Front frontFace;
	};
}

using CullFace = Renderer::CullFaceComponent::Cull;
using FrontFace = Renderer::CullFaceComponent::Front;