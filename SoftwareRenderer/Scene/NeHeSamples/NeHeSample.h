#pragma once
#include "../IScene.h"

class NeHeSample : public IScene
{
public:
	NeHeSample();
	~NeHeSample() override;

	void Init( std::shared_ptr<IRenderer> ) override;
	void Update( const Time& time ) override;
	void Render( std::shared_ptr<IRenderer> ) const override;
};

