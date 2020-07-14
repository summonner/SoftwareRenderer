#pragma once
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
	};

	using Degree = float;

public:
	virtual ~IRenderer() {}

	virtual void Clear() abstract;
	virtual void Present() abstract;

	virtual void Begin( DrawMode mode ) abstract;
	virtual void End() abstract;
	virtual void AddVertex( float x, float y, float z ) abstract;

	virtual void LoadIdentity() abstract;
	virtual void Translate( float x, float y, float z ) abstract;
	virtual void Rotate( Degree angle, float x, float y, float z ) abstract;
	virtual void Scale( float x, float y, float z ) abstract;
};

