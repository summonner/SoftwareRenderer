#include "framework.h"
#include "TextureComponent.h"
#include "ITexture.h"
#include "Renderer/Rasterizer/RasterizedPixel.h"

namespace Renderer
{
	TextureComponent::TextureComponent()
		: enabled( false )
	{
	}

	TextureComponent::~TextureComponent()
	{
	}

	void TextureComponent::SetEnable( bool enable )
	{
		enabled = enable;
	}

	void TextureComponent::Bind( std::shared_ptr<const ITexture> texture )
	{
		if ( enabled == false )
		{
			return;
		}

		this->texture = texture;
	}

	Vector4 TextureComponent::GetColor( const RasterizedPixel& p ) const
	{
		if ( texture == nullptr || enabled == false )
		{
			return Vector4::one;
		}

		const auto mipLevel = texture->CalculateMipLevel( p.ddx, p.ddy );
		return texture->GetPixel( p.GetTexcoord(), mipLevel );
	}
}