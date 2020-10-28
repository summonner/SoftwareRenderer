#pragma once
#include "Scene/IScene.h"
#include "Scene/IMouseInputListener.h"
#include "Scene/gl/glBridge.h"

namespace NeHe
{
	class ILesson;
}

class NeHeSample : public IScene, public IMouseInputListener
{
public:
	NeHeSample( std::unique_ptr<NeHe::ILesson> lesson );
	~NeHeSample() override;

	void Init( const std::shared_ptr<IRenderer> renderer ) override;
	void OnResize( const std::shared_ptr<IRenderer> renderer, const int width, const int height ) override;
	void Update( const Timer& time ) override;
	void OnKeyboardInput( BYTE keyCode, bool isPressed ) override;
	void Render( const std::shared_ptr<IRenderer> renderer ) const override;

	void OnMove( int x, int y ) override;
	void OnLButton( bool isPressed ) override;

private:
	const std::unique_ptr<NeHe::ILesson> lesson;
	const std::unique_ptr<glBridge> adapter;

	bool keys[256];
};

