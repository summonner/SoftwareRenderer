#include "framework.h"
#include "SceneFactory.h"

#include "NeHeSamples/NeHeSample.h"
#include "SampleScene.h"
#include "resource.h"

const Dictionary<UINT, SceneFactory::CreateFunc> SceneFactory::table(
{
	{ ID_SCENE_DEFAULT, Create<SampleScene> },
	{ ID_SCENE_NEHE, Create<NeHeSample> }
}, OnInvalidSceneId );

std::unique_ptr<IScene> SceneFactory::Create( std::shared_ptr<IRenderer> renderer, UINT resourceId )
{
	return table[resourceId]( renderer );
}

template<typename T>
std::unique_ptr<IScene> SceneFactory::Create( std::shared_ptr<IRenderer> renderer )
{
	return std::make_unique<T>( renderer );
}

std::unique_ptr<IScene> SceneFactory::OnInvalidSceneId( std::shared_ptr<IRenderer> renderer )
{
	return nullptr;
}