#pragma once

class Time;
class IRenderer;
class SampleScene
{
public:
	SampleScene();
	~SampleScene();

	void Update( const Time& time );
	void Render( std::shared_ptr<IRenderer> ) const;
};

