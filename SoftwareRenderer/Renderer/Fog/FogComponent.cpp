#include "framework.h"
#include "FogComponent.h"

namespace Renderer
{
	FogComponent::FogComponent()
		: mode( nullptr )
	{
		Reset();
	}

	FogComponent::~FogComponent()
	{
	}

	void FogComponent::Reset()
	{
		BaseComponent::Reset();
		mode = std::make_shared<FogFunc::Exp>( 1 );
	}

	void FogComponent::SetMode( const std::shared_ptr<const IFogFunc> mode )
	{
		this->mode = mode;
	}

	void FogComponent::SetColor( const Vector4& color )
	{
		fogColor = color;
	}

	Vector4 FogComponent::Apply( float depth, const Vector4& color ) const
	{
		if ( enabled == false )
		{
			return color;
		}

		const auto f = std::clamp( (*mode)( depth ), 0.f, 1.f );
		return Vector4(
			::Lerp( fogColor.x, color.x, f ),
			::Lerp( fogColor.y, color.y, f ),
			::Lerp( fogColor.z, color.z, f ),
			color.w
		);
	}
}