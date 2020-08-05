#include "framework.h"
#include "glLightManager.h"
#include "Renderer/Lighting/Light.h"
#include "Math/Radian.h"
using namespace Renderer;

glLightManager::glLightManager()
	: lights( maxLights )
{
}


glLightManager::~glLightManager()
{
}

void glLightManager::Set( GLenum light, GLenum pname, const GLfloat* params )
{
	const auto i = AsIndex( light );
	if ( lights[i] == nullptr )
	{
		lights[i] = std::make_shared<Light>();
	}

	switch ( pname )
	{
	case GL_AMBIENT:
		lights[i]->ambient = AsVector4( params );
		break;
	case GL_DIFFUSE:
		lights[i]->diffuse = AsVector4( params );
		break;
	case GL_SPECULAR:
		lights[i]->specular = AsVector4( params );
		break;
	case GL_POSITION:
		lights[i]->position = AsVector4( params );
		break;
	case GL_SPOT_DIRECTION:
		lights[i]->direction = AsVector3( params );
		break;
	case GL_SPOT_EXPONENT:
		lights[i]->exponent = AsFloat( params );
		break;
	case GL_SPOT_CUTOFF:
		lights[i]->cosCutoff = cos( Radian( AsFloat( params ) ) );
		break;
	case GL_CONSTANT_ATTENUATION:
		lights[i]->attenuation.x = AsFloat( params );
		break;
	case GL_LINEAR_ATTENUATION:
		lights[i]->attenuation.y = AsFloat( params );
		break;
	case GL_QUADRATIC_ATTENUATION:
		lights[i]->attenuation.z = AsFloat( params );
		break;
	}
}

std::shared_ptr<const Light> glLightManager::Get( GLenum light ) const
{
	const auto i = AsIndex( light );
	assert( i < maxLights );
	return lights[i];
}

int glLightManager::AsIndex( GLenum light )
{
	return light - GL_LIGHT0;
}

Vector4 glLightManager::AsVector4( const GLfloat* params )
{
	return Vector4( params[0], params[1], params[2], params[3] );
}

Vector3 glLightManager::AsVector3( const GLfloat* params )
{
	return Vector3( params[0], params[1], params[2] );
}

float glLightManager::AsFloat( const GLfloat* params )
{
	return params[0];
}