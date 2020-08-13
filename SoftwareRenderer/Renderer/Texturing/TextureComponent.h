#pragma once
#include "Renderer/IComponent.h"
#include "TexcoordFunc.h"

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

	public:
		TexcoordFunc texGen[2];

	private:
		std::shared_ptr<const ITexture> texture;
	};
}