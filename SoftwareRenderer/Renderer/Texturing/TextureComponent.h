#pragma once

namespace Renderer
{
	class RasterizedPixel;
	class ITexture;
	class TextureComponent final
	{
	public:
		TextureComponent();
		~TextureComponent();

		void SetEnable( bool enable );

		void Bind( std::shared_ptr<const ITexture> texture );

		Vector4 GetColor( const RasterizedPixel& p ) const;

	private:
		bool enabled;
		std::shared_ptr<const ITexture> texture;
	};
}