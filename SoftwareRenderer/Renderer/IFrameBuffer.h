#pragma once

class Bounds;
class IFrameBuffer abstract
{
public:
	virtual ~IFrameBuffer() {};

	virtual Bounds GetBounds() const abstract;
	virtual void Reset() abstract;
	virtual void Clear() abstract;
	virtual void SetClearValue( const Vector4& value ) abstract;
	virtual void SetPixel( const Vector2Int& p, const Vector4& color ) abstract;
	virtual void SetPixel( const Vector2Int& p, const Vector4& srcColor, std::function<Vector4( const Vector4&, const Vector4& )> blender ) abstract;
};