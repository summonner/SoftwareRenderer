#pragma once
#include "glAdapter.h"

namespace Renderer
{
	class Light;
}

class glLightManager final
{
public:
	glLightManager();
	~glLightManager();

	void Set( GLenum light, GLenum pname, const GLfloat* params );
	std::shared_ptr<const Renderer::Light> Get( GLenum light ) const;

private:
	std::vector<std::shared_ptr<Renderer::Light>> lights;

	static const int maxLights = 8;
	static int AsIndex( GLenum light );
	static Vector4 AsVector4( const GLfloat* params );
	static Vector3 AsVector3( const GLfloat* params );
	static float AsFloat( const GLfloat* params );
};

