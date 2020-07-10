#pragma once
class IRenderer abstract
{
public:
	enum class DrawMode
	{
		Points,
		Triangles,
	};

public:
	virtual ~IRenderer() {}

	virtual void Clear() abstract;
	virtual void Present() abstract;

	virtual void Begin( DrawMode mode ) abstract;
	virtual void End() abstract;
	virtual void Vertex( float x, float y, float z ) abstract;
};

