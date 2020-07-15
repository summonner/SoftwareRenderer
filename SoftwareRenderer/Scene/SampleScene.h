#pragma once
#include "IScene.h"

class SampleScene final : public IScene
{
public:
	SampleScene();
	~SampleScene() override;

	void Update( const Time& time ) override;
	void Render( std::shared_ptr<IRenderer> ) const override;
};

