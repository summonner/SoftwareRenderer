#include "framework.h"
#include "TextureComponent.h"
#include "ITexture.h"
#include "Renderer/Rasterizer/RasterizedPixel.h"
#include "Renderer/Rasterizer/DerivativeTexcoord.h"

namespace Renderer
{
	TextureComponent::TextureComponent()
		: texGen{ TexcoordFunc( Vector4( 1, 0, 0, 0 ) ), TexcoordFunc( Vector4( 0, 1, 0, 0 ) ) }
	{
	}

	TextureComponent::~TextureComponent()
	{
	}

	void TextureComponent::Reset()
	{
		BaseComponent::Reset();
		this->texture = nullptr;
	}

	void TextureComponent::Bind( std::shared_ptr<const ITexture> texture )
	{
		this->texture = texture;
	}

	Vector4 TextureComponent::GetColor( const RasterizedPixel& p, const DerivativeTexcoord& derivatives ) const
	{
		if ( texture == nullptr || enabled == false )
		{
			return Vector4::one;
		}

		if ( derivatives.IsValid() == false )
		{
			return texture->GetPixel( p.GetTexcoord(), 0 );
		}

		const auto& values = p.GetRawValues();
		const auto ddx = derivatives.dFdx( values.texcoord, values.w );
		const auto ddy = derivatives.dFdy( values.texcoord, values.w );
		const auto mipLevel = texture->CalculateMipLevel( ddx, ddy );
		return texture->GetPixel( p.GetTexcoord(), mipLevel );
	}
}