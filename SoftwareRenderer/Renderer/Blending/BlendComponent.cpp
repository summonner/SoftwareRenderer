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

	void BlendComponent::SetEnable( const bool enable )
	{
		enabled = enable;
	}

	bool BlendComponent::IsEnable() const
	{
		return enabled;
	}

	Vector4 BlendComponent::operator ()( const Vector4& srcColor, const Vector4& dstColor ) const
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