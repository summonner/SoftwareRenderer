#include "framework.h"
#include "glBridge.h"

glBridge::glBridge()
	: renderer( nullptr )
{
}

glBridge::~glBridge()
{
}


void glBridge::Use( std::function<void( void )> process )
{
	::adapter = this;
	process();
	::adapter = nullptr;
}