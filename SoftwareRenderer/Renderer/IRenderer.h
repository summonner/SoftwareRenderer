#pragma once
#undef near
#undef far

class IRenderer abstract
{
public:
	enum class DrawMode
	{
		Points,
		Lines,
		LineStrip,
		LineLoop,
		Triangles,
		TriangleStrip,
		TriangleFan,
		Quads,
	};

	using Degree = float;

public:
	virtual ~IRenderer() {}

	virtual void Clear() abstract;
	virtual void Present() abstract;

	virtual void Begin( DrawMode mode ) abstract;
	virtual void End() abstract;
	virtual void SetColor( float r, float g, float b ) abstract;
	virtual void AddVertex( float x, float y, float z ) abstract;

	virtual void LoadIdentity() abstract;
	virtual void Translate( float x, float y, float z ) abstract;
	virtual void Rotate( Degree angle, float x, float y, float z ) abstract;
	virtual void Scale( float x, float y, float z ) abstract;

	virtual void Viewport( float left, float top, float width, float height ) abstract;
	virtual void Frustum( float left, float right, float top, float bottom, float near, float far ) abstract;
	virtual void Perspective( Degree fovY, float aspect, float near, float far ) abstract;
	virtual void Ortho( float left, float right, float top, float bottom, float near, float far ) abstract;
};

