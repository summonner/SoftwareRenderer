#pragma once
#include "IScene.h"
#include "gl/glBridge.h"

namespace Renderer
{
	class Texture2D;
	class Light;
}

class SampleScene final : public IScene
{
public:
	SampleScene();
	~SampleScene() override;

	void Init( const std::shared_ptr<IRenderer> renderer ) override;
	void OnResize( const std::shared_ptr<IRenderer> renderer, const int width, const int height ) override;
	void Update( const Time& time ) override;
	void Render( const std::shared_ptr<IRenderer> renderer ) const override;

private:
	void Floor() const;
	void Triangle() const;
	void Quad() const;
	void Cube() const;

	void PointerTest() const;
	void IndexTest() const;
	void Quadric() const;

private:
	std::shared_ptr<Renderer::Texture2D> texture;
	std::shared_ptr<Renderer::Light> light;
	void DrawScene() const;

private:
	std::unique_ptr<glBridge> adapter;
};

