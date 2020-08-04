#pragma once
#include "Renderer/IComponent.h"

namespace Renderer
{
	class RasterizedPixel;
	class ITexture;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent();
		~TextureComponent();

		void Bind( std::shared_ptr<const ITexture> texture );

		Vector4 GetColor( const RasterizedPixel& p ) const;

	private:
		std::shared_ptr<const ITexture> texture;
	};
}