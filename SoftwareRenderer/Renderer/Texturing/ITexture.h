#pragma once
namespace Renderer
{
	class ITexture abstract
	{
	public:
		virtual ~ITexture() {}

		virtual Vector4 GetPixel( const Vector2& uv ) const abstract;
	};
}