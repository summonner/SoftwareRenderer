#pragma once
#include "Renderer/IComponent.h"

namespace Renderer
{
	class RasterizedPixel;
	class ITexture;
	class DerivativeTexcoord;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent();
		~TextureComponent();

		void Reset() override;
		void Bind( std::shared_ptr<const ITexture> texture );

		Vector4 GetColor( const RasterizedPixel& p, const DerivativeTexcoord& derivatives ) const;

	private:
		std::shared_ptr<const ITexture> texture;
	};
}