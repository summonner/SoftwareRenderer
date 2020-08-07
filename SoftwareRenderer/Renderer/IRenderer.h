#pragma once
#undef near
#undef far
#include "Texturing/TextureComponent.h"
#include "DepthTest/DepthBuffer.h"
#include "Blending/BlendComponent.h"
#include "CullFace/CullFaceComponent.h"
#include "Lighting/LightingComponent.h"
#include "Mesh/Mesh.h"

namespace Renderer
{
	class Vertex;
}

class Degree;
class IRenderer abstract
{

public:
	IRenderer( int width, int height )
		: depthBuffer( width, height )
	{
	}

	virtual ~IRenderer() {}

	virtual void Clear() abstract;
	virtual void SetClearColor( float r, float g, float b, float a ) abstract;
	virtual void Present() abstract;

	virtual void Draw( const Renderer::Mesh& mesh ) abstract;

	virtual void LoadIdentity() abstract;
	virtual void Translate( float x, float y, float z ) abstract;
	virtual void Rotate( Degree angle, float x, float y, float z ) abstract;
	virtual void Scale( float x, float y, float z ) abstract;

	virtual void Viewport( int left, int top, int width, int height ) abstract;
	virtual void Frustum( float left, float right, float top, float bottom, float near, float far ) abstract;
	virtual void Perspective( Degree fovY, float aspect, float near, float far ) abstract;
	virtual void Ortho( float left, float right, float top, float bottom, float near, float far ) abstract;

	virtual void Reset()
	{
		depthBuffer.Reset();
		texture.Reset();
		cullFace.Reset();
		lighting.Reset();
		blender.Reset();
	}

public:
	Renderer::TextureComponent texture;
	Renderer::DepthBuffer depthBuffer;
	Renderer::BlendComponent blender;
	Renderer::CullFaceComponent cullFace;
	Renderer::LightingComponent lighting;
};

