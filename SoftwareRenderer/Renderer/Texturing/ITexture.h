#pragma once
namespace Renderer
{
	class ITexture abstract
	{
	public:
		enum class WrapMode
		{
			Clamp,
			Repeat,
			MirroredRepeat,
		};
	public:
		virtual ~ITexture() {}

		virtual Vector4 GetPixel( const Vector2& uv ) const abstract;
	};
}