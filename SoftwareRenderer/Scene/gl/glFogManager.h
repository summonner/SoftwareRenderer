#pragma once
#include "glAdapter.h"
#include "Renderer/Fog/FogFunc.h"

class glFogManager
{
public:
	glFogManager();
	~glFogManager();

	void SetDensity( GLfloat param );
	void SetStart( GLfloat param );
	void SetEnd( GLfloat param );
	std::shared_ptr<const Renderer::IFogFunc> SetMode( GLint param );
	std::shared_ptr<const Renderer::IFogFunc> GetMode() const;

private:
	std::shared_ptr<const Renderer::IFogFunc> current;
	std::shared_ptr<Renderer::FogFunc::Linear> linear;
	std::shared_ptr<Renderer::FogFunc::Exp> exp;
	std::shared_ptr<Renderer::FogFunc::Exp> exp2;
};

