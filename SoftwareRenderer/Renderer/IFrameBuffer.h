#pragma once

class Bounds;
namespace Renderer
{
	class IFrameBufferController abstract
	{
	public:
		virtual ~IFrameBufferController() {};

		virtual void Reset() abstract;
		virtual void Clear() abstract;

		virtual void SetClearValue( const Vector4& value ) abstract;
		virtual Vector4 GetPixel( const Vector2Int& p ) const abstract;
	};

	class IFrameBuffer abstract : public IFrameBufferController
	{
	public:
		virtual ~IFrameBuffer() {};

		virtual Bounds GetBounds() const abstract;
		virtual void Clear( const Bounds& bound ) abstract;
		virtual void SetPixel( const Vector2Int& p, const Vector4& color ) abstract;
		virtual void SetPixel( const Vector2Int& p, const Vector4& srcColor, std::function<Vector4( const Vector4&, const Vector4& )> blender ) abstract;
	};
}