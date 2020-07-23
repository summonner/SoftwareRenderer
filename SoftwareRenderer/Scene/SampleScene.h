#pragma once
#include "IScene.h"
#include "Util/Bitmap.h"

class SampleScene final : public IScene
{
public:
	SampleScene();
	~SampleScene() override;

	void Init( std::shared_ptr<IRenderer> renderer ) override;
	void Update( const Time& time ) override;
	void Render( std::shared_ptr<IRenderer> renderer ) const override;

private:
	std::shared_ptr<const Bitmap> checker;
	void DrawScene() const;
};

