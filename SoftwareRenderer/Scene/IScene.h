#pragma once

class Time;
class IRenderer;
class IScene abstract
{
public:
	virtual ~IScene() {}

	virtual void Update( const Time& time ) abstract;
	virtual void Render( std::shared_ptr<IRenderer> ) const abstract;
};
