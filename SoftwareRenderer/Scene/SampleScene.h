#pragma once
#include "IScene.h"

namespace Renderer
{
	class Texture2D;
	class Light;
}

class SampleScene final : public IScene
{
public:
	SampleScene( std::shared_ptr<IRenderer> renderer );
	~SampleScene() override;

	void Update( const Time& time ) override;
	void Render( std::shared_ptr<IRenderer> renderer ) const override;

private:
	void Floor() const;
	void Triangle() const;
	void Quad() const;
	void Cube() const;

	void PointerTest() const;

private:
	std::shared_ptr<Renderer::Texture2D> texture;
	std::shared_ptr<Renderer::Light> light;
	void DrawScene() const;
};

