#include "framework.h"
#include "glDisplayList.h"
#include "glBridge.h"

void glDisplayList::Push( Command command )
{
	commands.push_back( command );
}

void glDisplayList::Call( glBridge* adapter ) const
{
	for ( const auto& command : commands )
	{
		command( adapter );
	}
}