#pragma once
#include "IScene.h"

class IRenderer;
class SceneFactory final abstract
{
public:
	static std::unique_ptr<IScene> Create( std::shared_ptr<IRenderer> renderer, int resourceId );

private:
	template<typename T>
	static std::unique_ptr<IScene> Create( std::shared_ptr<IRenderer> renderer );

	using CreateFunc = std::function<std::unique_ptr<IScene>( std::shared_ptr<IRenderer> )>;
	static std::map<int, CreateFunc> table;
};