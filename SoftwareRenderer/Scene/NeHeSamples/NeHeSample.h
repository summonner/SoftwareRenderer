#pragma once
#include "../IScene.h"

namespace NeHe
{
	class ILesson;
}

class NeHeSample : public IScene
{
public:
	NeHeSample( std::shared_ptr<IRenderer> renderer, std::unique_ptr<NeHe::ILesson> lesson );
	~NeHeSample() override;

	void Update( const Time& time ) override;
	void Render( std::shared_ptr<IRenderer> ) const override;

private:
	std::unique_ptr<NeHe::ILesson> lesson;
};

