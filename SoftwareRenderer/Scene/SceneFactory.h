#pragma once
#include "IScene.h"
#include "Util/Dictionary.hpp"

class IRenderer;
class SceneFactory final abstract
{
public:
	static const UINT defaultScene;
	static const std::pair<UINT, UINT> sceneRange;
	static std::unique_ptr<IScene> Create( UINT resourceId );

private:
	template<typename T>
	static std::unique_ptr<IScene> Create();
	template<class Lesson>
	static std::unique_ptr<IScene> NeHeLesson();
	static std::unique_ptr<IScene> ReturnNullPtr();

	using CreateFunc = std::function<std::unique_ptr<IScene>( void )>;
	static const Dictionary<UINT, CreateFunc> table;
};