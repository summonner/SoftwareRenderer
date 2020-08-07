#pragma once
#include "Scene/IScene.h"
#include "Scene/gl/glBridge.h"

namespace NeHe
{
	class ILesson;
}

class NeHeSample : public IScene
{
public:
	NeHeSample( std::unique_ptr<NeHe::ILesson> lesson );
	~NeHeSample() override;

	void Init( const std::shared_ptr<IRenderer> renderer ) override;
	void OnResize( const std::shared_ptr<IRenderer> renderer, const int width, const int height ) override;
	void Update( const Time& time ) override;
	void Render( const std::shared_ptr<IRenderer> renderer ) const override;

private:
	const std::unique_ptr<NeHe::ILesson> lesson;
	const std::unique_ptr<glBridge> adapter;
};

