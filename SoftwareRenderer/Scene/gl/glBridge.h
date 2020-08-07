#pragma once
#include "Renderer/IRenderer.h"
#include "glTextureManager.h"
#include "glLightManager.h"
#include "glBufferManager.h"

class glBridge;
extern glBridge* adapter;

class glBridge final
{
public:
	glBridge();
	~glBridge();

	void Use( IRenderer* renderer, std::function<void( void )> process );

	IRenderer* renderer;
	glTextureManager textureManager;
	glLightManager lightManager;
	glBufferManager bufferManager;
};