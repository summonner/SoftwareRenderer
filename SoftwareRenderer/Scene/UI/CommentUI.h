#pragma once
#include "UI.h"

class CommentUI abstract final
{
public:
	static void Print( IRenderer& renderer, const char* comment );

private:
	static UI ui;
};