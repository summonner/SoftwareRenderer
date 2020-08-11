#include "framework.h"
#include "glBridge.h"

glBridge::glBridge()
	: renderer( nullptr )
	, matrix( nullptr )
{
}

glBridge::~glBridge()
{
}

void glBridge::Init( std::shared_ptr<IRenderer> renderer )
{
	this->renderer = renderer;
	matrix = &(renderer->modelView);
}

void glBridge::Use( std::function<void( void )> process )
{
	::adapter = this;
	process();
	::adapter = nullptr;
}