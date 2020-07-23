#include "framework.h"
#include "SceneFactory.h"

#include "NeHeSamples/NeHeSample.h"
#include "SampleScene.h"
#include "resource.h"

std::map<int, SceneFactory::CreateFunc> SceneFactory::table =
{
	{ ID_SCENE_DEFAULT, Create<SampleScene> },
	{ ID_SCENE_NEHE, Create<NeHeSample> }
};

std::unique_ptr<IScene> SceneFactory::Create( std::shared_ptr<IRenderer> renderer, int resourceId )
{
	if ( const auto& found{ table.find( resourceId ) }; found != table.end() )
	{
		return found->second( renderer );
	}
	else
	{
		return nullptr;
	}
}

template<typename T>
std::unique_ptr<IScene> SceneFactory::Create( std::shared_ptr<IRenderer> renderer )
{
	return std::make_unique<T>( renderer );
}