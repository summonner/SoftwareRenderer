#pragma once
#include "Renderer/IRenderer.h"
#include "glTextureManager.h"
#include "glLightManager.h"
#include "glMeshBuilder.h"
#include "glTexcoordGenerator.h"
#include "glClipPlaneManager.h"
#include "glDisplayListManager.h"
#include "ICommandBuffer.h"
#include "glFogManager.h"

class glBridge;
extern glBridge* adapter;
extern ICommandBuffer* commandBuffer;

class glBridge final : public ICommandBuffer
{
public:
	glBridge();
	~glBridge();

	void Init( std::shared_ptr<IRenderer> renderer );
	void Use( std::function<void( void )> process );
	void Push( Command command ) override;

	std::shared_ptr<IRenderer> renderer;
	glTextureManager textureManager;
	glLightManager lightManager;
	glMeshBuilder meshBuilder;
	glTexcoordGenerator texcoordGenerator;
	glClipPlaneManager clipPlaneManager;
	glDisplayListManager displayListManager;
	glFogManager fogManager;

	Renderer::Matrix* matrix;
};