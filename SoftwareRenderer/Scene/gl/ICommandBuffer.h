#pragma once

class glBridge;
class ICommandBuffer abstract
{
public:
	using Command = std::function<void( glBridge* )>;
	virtual void Push( Command command ) abstract;
};

