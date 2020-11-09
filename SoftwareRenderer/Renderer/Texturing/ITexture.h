#pragma once
namespace Renderer
{
	class ITexture abstract
	{
	public:
		virtual ~ITexture() {}

		virtual float CalculateMipLevel( Vector2 ddx, Vector2 ddy ) const abstract;
		virtual Vector4 GetPixel( const Vector2& uv, const float mipLevel ) const abstract;
		virtual bool IsValid() const abstract;
	};
}