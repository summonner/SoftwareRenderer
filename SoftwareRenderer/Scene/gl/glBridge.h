#pragma once
#include "Renderer/IRenderer.h"
#include "glTextureManager.h"
#include "glLightManager.h"
#include "glMeshBuilder.h"
#include "glTexcoordGenerator.h"

class glBridge;
extern glBridge* adapter;

class glBridge final
{
public:
	glBridge();
	~glBridge();

	void Init( std::shared_ptr<IRenderer> renderer );
	void Use( std::function<void( void )> process );

	std::shared_ptr<IRenderer> renderer;
	glTextureManager textureManager;
	glLightManager lightManager;
	glMeshBuilder meshBuilder;
	glTexcoordGenerator texcoordGenerator;

	Renderer::Matrix* matrix;
};