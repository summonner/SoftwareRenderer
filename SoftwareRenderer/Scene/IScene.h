#pragma once

class Time;
class IRenderer;
class IScene abstract
{
public:
	virtual ~IScene() {}

	virtual void Init( const std::shared_ptr<IRenderer> renderer ) abstract;
	virtual void OnResize( const std::shared_ptr<IRenderer> renderer, const int width, const int height ) abstract;
	virtual void Update( const Time& time ) abstract;
	virtual void Render( const std::shared_ptr<IRenderer> renderer ) const abstract;
};
