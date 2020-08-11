#pragma once
#include "Texturing/TextureComponent.h"
#include "DepthTest/DepthBuffer.h"
#include "Blending/BlendComponent.h"
#include "CullFace/CullFaceComponent.h"
#include "Lighting/LightingComponent.h"
#include "Rasterizer/ShadeModel.h"
#include "Mesh/Mesh.h"
#include "Matrix.h"

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

	virtual void Reset()
	{
		depthBuffer.Reset();
		texture.Reset();
		cullFace.Reset();
		lighting.Reset();
		blender.Reset();
		Renderer::ShadeModel::type = Renderer::ShadeModel::Type::Smooth;
	}

public:
	Renderer::TextureComponent texture;
	Renderer::DepthBuffer depthBuffer;
	Renderer::BlendComponent blender;
	Renderer::CullFaceComponent cullFace;
	Renderer::LightingComponent lighting;

	Renderer::Matrix modelView;
	Renderer::Matrix projection;
	Renderer::Matrix viewport;
};

