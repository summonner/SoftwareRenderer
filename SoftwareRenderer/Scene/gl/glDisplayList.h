#pragma once
#include "ICommandBuffer.h"

class glBridge;
class glDisplayList final : public ICommandBuffer
{
public:
	void Push( Command command );
	void Call( glBridge* adapter ) const;

private:
	std::vector<Command> commands;
};

