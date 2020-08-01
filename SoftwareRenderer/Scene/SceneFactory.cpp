#include "framework.h"
#include "SceneFactory.h"

#include "NeHeSamples/NeHeSample.h"
#include "NeHeSamples/LessonList.h"
#include "SampleScene.h"
#include "resource.h"

const Dictionary<UINT, SceneFactory::CreateFunc> SceneFactory::table(
{
	{ ID_SCENE_DEFAULT, Create<SampleScene> },
	{ ID_NEHE_LESSON6, NeHeLesson<NeHe::Lesson6> },
	{ ID_NEHE_LESSON8, NeHeLesson<NeHe::Lesson8> },
}, ReturnNullPtr );

std::unique_ptr<IScene> SceneFactory::Create( std::shared_ptr<IRenderer> renderer, UINT resourceId )
{
	return table[resourceId]( renderer );
}

template<typename T>
std::unique_ptr<IScene> SceneFactory::Create( std::shared_ptr<IRenderer> renderer )
{
	return std::make_unique<T>( renderer );
}

template<class Lesson>
std::unique_ptr<IScene> SceneFactory::NeHeLesson( std::shared_ptr<IRenderer> renderer )
{
	return std::make_unique<NeHeSample>( renderer, std::make_unique<Lesson>() );
}

std::unique_ptr<IScene> SceneFactory::ReturnNullPtr( std::shared_ptr<IRenderer> renderer )
{
	return nullptr;
}