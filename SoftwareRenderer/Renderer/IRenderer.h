#pragma once
#include "Generators/GeometryGenerator.h"
#include "Texturing/TextureComponent.h"
#include "DepthTest/DepthBuffer.h"
#include "Blending/BlendComponent.h"
#include "CullFace/CullFaceComponent.h"
#include "Lighting/LightingComponent.h"
#include "Rasterizer/ShadeModel.h"
#include "Mesh/Mesh.h"
#include "StencilTest/StencilBuffer.h"
#include "Clipping/CustomClipPlanes.h"
#include "Matrix.h"
#include "Viewport.h"
#include "IFrameBuffer.h"

namespace Renderer
{
	class Vertex;
}

class IRenderer
{
public:
	IRenderer( std::unique_ptr<Renderer::IFrameBuffer> frameBuffer );
	~IRenderer();

	void Draw( const Renderer::Mesh& mesh );

	void Reset();

private:
	Renderer::Vertex ProcessVertex( Renderer::Vertex v ) const;

	Renderer::GeometryGenerator generator;
	std::vector<Renderer::Vertex> vertices;

private:
	const std::unique_ptr<Renderer::IFrameBuffer> backBuffer;
	Renderer::DepthBuffer depthBuffer;
	Renderer::StencilBuffer stencilBuffer;

public:
	Renderer::IDepthBufferController& GetDepthBuffer();
	Renderer::IFrameBufferController& GetFrameBuffer();
	Renderer::IStencilBufferController& GetStencilBuffer();

	Renderer::TextureComponent texture;
	Renderer::BlendComponent blender;
	Renderer::CullFaceComponent cullFace;
	Renderer::LightingComponent lighting;
	Renderer::CustomClipPlanes planes;

	Renderer::Matrix modelView;
	Renderer::Matrix projection;
	Renderer::Viewport viewport;
};

