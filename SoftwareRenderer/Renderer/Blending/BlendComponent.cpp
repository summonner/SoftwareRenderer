#include "framework.h"
#include "BlendComponent.h"
#include "Math/Vector4.hpp"

namespace Renderer
{
	BlendComponent::BlendComponent()
		: srcFunc( BlendFunc::Type::One )
		, dstFunc( BlendFunc::Type::Zero )
	{
	}

	BlendComponent::~BlendComponent()
	{
	}

	std::function<Vector4( const Vector4&, const Vector4& )> BlendComponent::AsFunc() const
	{
		if ( enabled == false )
		{
			return nullptr;
		}

		return std::bind( &BlendComponent::Apply, *this, std::placeholders::_1, std::placeholders::_2 );
	}

	Vector4 BlendComponent::Apply( const Vector4& srcColor, const Vector4& dstColor ) const
	{
		const auto srcFactor = srcFunc( srcColor, dstColor );
		const auto dstFactor = dstFunc( srcColor, dstColor );
		return srcColor * srcFactor + dstColor * dstFactor;
	}

	void BlendComponent::SetBlendFunc( const BlendFunc::Type src, const BlendFunc::Type dst )
	{
		srcFunc = src;
		dstFunc = dst;
	}

	void BlendComponent::SetBlendColor( const Vector4& color )
	{
		BlendFunc::constant = color;
	}
}