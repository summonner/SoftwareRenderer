#pragma once
#include "IScene.h"
#include "Util/Dictionary.hpp"

class IRenderer;
class SceneFactory final abstract
{
public:
	static const UINT defaultScene;
	static const std::pair<UINT, UINT> sceneRange;
	static std::unique_ptr<IScene> Create( std::shared_ptr<IRenderer> renderer, UINT resourceId );

private:
	template<typename T>
	static std::unique_ptr<IScene> Create( std::shared_ptr<IRenderer> renderer );
	template<class Lesson>
	static std::unique_ptr<IScene> NeHeLesson( std::shared_ptr<IRenderer> renderer );
	static std::unique_ptr<IScene> ReturnNullPtr( std::shared_ptr<IRenderer> renderer );

	using CreateFunc = std::function<std::unique_ptr<IScene>( std::shared_ptr<IRenderer> )>;
	static const Dictionary<UINT, CreateFunc> table;
};