#pragma once
class IRenderer
{
public:
	virtual ~IRenderer();

	virtual void Clear() = 0;
	virtual void Present() = 0;
};

