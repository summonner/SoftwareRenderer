#pragma once
#include "IScene.h"
#include "Renderer/Mesh/Mesh.h"

class AntiAliasingScene : public IScene
{
public:
	AntiAliasingScene();
	~AntiAliasingScene();

	void Init( const std::shared_ptr<IRenderer> renderer ) override;
	void OnResize( const std::shared_ptr<IRenderer> renderer, const int width, const int height ) override;
	void Update( const Timer& time ) override;
	void OnKeyboardInput( BYTE keyCode, bool isPressed ) override;
	void Render( const std::shared_ptr<IRenderer> renderer ) const override;

private:
	void Lines( IRenderer& renderer ) const;
	void Points( IRenderer& renderer ) const;

private:
	bool enableAA;
	int shape;
	float t;

	Renderer::Mesh line;

private:
	static Renderer::Mesh BuildLine();
};

