#include "framework.h"
#include "SceneFactory.h"

#include "NeHeSamples/NeHeSample.h"
#include "NeHeSamples/LessonList.h"
#include "SampleScene.h"
#include "resource.h"

const UINT SceneFactory::defaultScene = ID_SCENE_DEFAULT;
const std::pair<UINT, UINT> SceneFactory::sceneRange = { ID_SCENE_NEHE, ID_NEHE_LESSON48 };

#define NEHE( n )\
	{ ID_NEHE_LESSON##n, NeHeLesson<NeHe::Lesson##n> }

const Dictionary<UINT, SceneFactory::CreateFunc> SceneFactory::table(
{
	{ ID_SCENE_DEFAULT, Create<SampleScene> },
	NEHE(  2 ),
	NEHE(  3 ),
	NEHE(  4 ),
	NEHE(  5 ),
	NEHE(  6 ),
	NEHE(  7 ),
	NEHE(  8 ),
	NEHE( 10 ),
	NEHE( 17 ),
	NEHE( 18 ),
	NEHE( 23 ),
	NEHE( 26 ),
	NEHE( 36 ),
	NEHE( 45 ),
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