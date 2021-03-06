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
#include "Rasterizer/PolygonMode.h"
#include "Fog/FogComponent.h"

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

	using RasterizeFunc = std::function<void( Renderer::IRasterizer& rasterizer, const Bounds& bounds)>;
	void Draw( const Renderer::Mesh& mesh, RasterizeFunc rasterize );

	void Reset();

private:
	Renderer::Vertex ProcessVertex( Renderer::Vertex v ) const;
	void Rasterize( Renderer::IRasterizer& rasterizer, const Bounds& bounds );

	Renderer::GeometryGenerator generator;
	std::vector<Renderer::Vertex> vertices;

private:
	const std::unique_ptr<Renderer::IFrameBuffer> backBuffer;
	Renderer::DepthBuffer depthBuffer;
	Renderer::StencilBuffer stencilBuffer;

public:
	Renderer::IDepthBufferController& GetDepthBuffer();
	const Renderer::IDepthBufferController& GetDepthBuffer() const;
	Renderer::IFrameBufferController& GetFrameBuffer();
	Renderer::IStencilBufferController& GetStencilBuffer();
	const Renderer::IStencilBufferController& GetStencilBuffer() const;

	Renderer::TextureComponent texture;
	Renderer::BlendComponent blender;
	Renderer::CullFaceComponent cullFace;
	Renderer::LightingComponent lighting;
	Renderer::CustomClipPlanes planes;
	Renderer::PolygonMode polygonMode;
	Renderer::FogComponent fog;

	Renderer::Matrix modelView;
	Renderer::Matrix projection;
	Renderer::Viewport viewport;
};

