#pragma once
#include "IScene.h"

namespace Renderer
{
	class Texture2D;
}

class SampleScene final : public IScene
{
public:
	SampleScene( std::shared_ptr<IRenderer> renderer );
	~SampleScene() override;

	void Update( const Time& time ) override;
	void Render( std::shared_ptr<IRenderer> renderer ) const override;

private:
	std::shared_ptr<Renderer::Texture2D> checker;
	void DrawScene() const;
};

