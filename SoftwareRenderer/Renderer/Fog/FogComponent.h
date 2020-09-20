#pragma once
#include "Renderer/IComponent.h"
#include "FogFunc.h"
#include "Math/Vector4.hpp"

namespace Renderer
{
	class FogComponent : public BaseComponent
	{
	public:
		FogComponent();
		~FogComponent();

		void Reset() override;
		Vector4 Apply( float depth, const Vector4& color ) const;
		void SetMode( const std::shared_ptr<const IFogFunc> mode );
		void SetColor( const Vector4& color );

	private:
		std::shared_ptr<const IFogFunc> mode;
		Vector4 fogColor;
	};
}