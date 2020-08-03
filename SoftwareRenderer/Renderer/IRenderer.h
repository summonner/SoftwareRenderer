#pragma once
#undef near
#undef far
#include "Texturing/TextureComponent.h"
#include "DepthTest/DepthBuffer.h"
#include "Blending/BlendComponent.h"
#include "CullFace/CullFaceComponent.h"

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
	IRenderer( int width, int height )
		: depthBuffer( width, height )
	{
	}

	virtual ~IRenderer() {}

	virtual void Clear() abstract;
	virtual void SetClearColor( float r, float g, float b, float a ) abstract;
	virtual void Present() abstract;

	virtual void Begin( DrawMode mode ) abstract;
	virtual void End() abstract;
	virtual void Color( float r, float g, float b, float a ) abstract;
	virtual void TexCoord( float u, float v ) abstract;
	virtual void AddVertex( float x, float y, float z ) abstract;

	virtual void LoadIdentity() abstract;
	virtual void Translate( float x, float y, float z ) abstract;
	virtual void Rotate( Degree angle, float x, float y, float z ) abstract;
	virtual void Scale( float x, float y, float z ) abstract;

	virtual void Viewport( int left, int top, int width, int height ) abstract;
	virtual void Frustum( float left, float right, float top, float bottom, float near, float far ) abstract;
	virtual void Perspective( Degree fovY, float aspect, float near, float far ) abstract;
	virtual void Ortho( float left, float right, float top, float bottom, float near, float far ) abstract;

public:
	Renderer::TextureComponent texture;
	Renderer::DepthBuffer depthBuffer;
	Renderer::BlendComponent blender;
	Renderer::CullFaceComponent cullFace;
};

