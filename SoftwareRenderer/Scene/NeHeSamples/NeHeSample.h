#pragma once
#include "../IScene.h"

class NeHeSample : public IScene
{
public:
	NeHeSample();
	~NeHeSample() override;

	void Update( const Time& time ) override;
	void Render( std::shared_ptr<IRenderer> ) const override;
};

