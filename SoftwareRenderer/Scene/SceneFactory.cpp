#include "framework.h"
#include "SceneFactory.h"

#include "NeHeSamples/NeHeSample.h"
#include "NeHeSamples/LessonList.h"
#include "SampleScene.h"
#include "resource.h"

const UINT SceneFactory::defaultScene = ID_SCENE_DEFAULT;
const std::pair<UINT, UINT> SceneFactory::sceneRange = { ID_SCENE_NEHE, ID_NEHE_LESSON45 };

const Dictionary<UINT, SceneFactory::CreateFunc> SceneFactory::table(
{
	{ ID_SCENE_DEFAULT, Create<SampleScene> },
	{ ID_NEHE_LESSON6, NeHeLesson<NeHe::Lesson6> },
	{ ID_NEHE_LESSON8, NeHeLesson<NeHe::Lesson8> },
	{ ID_NEHE_LESSON45, NeHeLesson<NeHe::Lesson45> },
}, ReturnNullPtr );

std::unique_ptr<IScene> SceneFactory::Create( UINT resourceId )
{
	return table[resourceId]();
}

template<typename T>
std::unique_ptr<IScene> SceneFactory::Create()
{
	return std::make_unique<T>();
}

template<class Lesson>
std::unique_ptr<IScene> SceneFactory::NeHeLesson()
{
	return std::make_unique<NeHeSample>( std::make_unique<Lesson>() );
}

std::unique_ptr<IScene> SceneFactory::ReturnNullPtr()
{
	return nullptr;
}