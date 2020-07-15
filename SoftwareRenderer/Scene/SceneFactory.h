#pragma once
#include "IScene.h"

class SceneFactory abstract	// to prevent instantiation
{
public:
	static std::unique_ptr<IScene> Create();
};