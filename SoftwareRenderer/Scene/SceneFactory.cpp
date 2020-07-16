#include "framework.h"
#include "SceneFactory.h"

#include "NeHeSamples/NeHeSample.h"
#include "SampleScene.h"


std::unique_ptr<IScene> SceneFactory::Create()
{
	return std::make_unique<SampleScene>();
//	return std::make_unique<NeHeSample>();
}