#include "framework.h"
#include "glBridge.h"

glBridge::glBridge()
{
}

glBridge::~glBridge()
{
}


void glBridge::Use( IRenderer* renderer, std::function<void( void )> process )
{
	::adapter = this;
	this->renderer = renderer;
	process();
	this->renderer = nullptr;
	::adapter = nullptr;
}