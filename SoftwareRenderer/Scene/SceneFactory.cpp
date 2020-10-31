#include "framework.h"
#include "SceneFactory.h"

#include "NeHeSamples/NeHeSample.h"
#include "NeHeSamples/LessonList.h"
#include "SampleScene.h"
#include "AntiAliasingScene.h"
#include "resource.h"

const UINT SceneFactory::defaultScene = ID_SCENE_DEFAULT;
const std::pair<UINT, UINT> SceneFactory::sceneRange = { ID_SCENE_NEHE, ID_SCENE_ANTIALIASING };

#define NEHE( n )\
	{ ID_NEHE_LESSON##n, NeHeLesson<NeHe::Lesson##n> }

const Dictionary<UINT, SceneFactory::CreateFunc> SceneFactory::table(
{
	{ ID_SCENE_DEFAULT, Create<SampleScene> },
	{ ID_SCENE_ANTIALIASING, Create<AntiAliasingScene> },
	NEHE(  2 ),
	NEHE(  3 ),
	NEHE(  4 ),
	NEHE(  5 ),
	NEHE(  6 ),
	NEHE(  7 ),
	NEHE(  8 ),
	NEHE(  9 ),
	NEHE( 10 ),
	NEHE( 11 ),
	NEHE( 12 ),
	NEHE( 16 ),
	NEHE( 17 ),
	NEHE( 18 ),
	NEHE( 19 ),
	NEHE( 20 ),
	NEHE( 21 ),
	NEHE( 22 ),
	NEHE( 23 ),
	NEHE( 24 ),
	NEHE( 25 ),
	NEHE( 26 ),
	NEHE( 27 ),
	NEHE( 28 ),
	NEHE( 29 ),
	NEHE( 30 ),
	NEHE( 31 ),
	NEHE( 32 ),
	NEHE( 33 ),
	NEHE( 34 ),
	NEHE( 35 ),
	NEHE( 36 ),
	NEHE( 37 ),
	NEHE( 38 ),
	NEHE( 39 ),
	NEHE( 40 ),
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