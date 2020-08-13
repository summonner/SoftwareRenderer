#include "framework.h"
#include "glTexcoordGenerator.h"
#include "Renderer/Texturing/TextureComponent.h"

glTexcoordGenerator::glTexcoordGenerator()
{
}

glTexcoordGenerator::~glTexcoordGenerator()
{
}

void glTexcoordGenerator::SetMode( Renderer::TextureComponent& component, GLenum coord, GLint param )
{
	const Dictionary<GLint, TexcoordFunc> table
	{
		{ GL_OBJECT_LINEAR, TexcoordFunc::ObjectLinear },
		{ GL_EYE_LINEAR, TexcoordFunc::EyeLinear },
		{ GL_SPHERE_MAP, TexcoordFunc::Sphere },
	};

	const int i = GetCoordIndex( coord );
	type[i] = table[param];
	const int j = param - GL_EYE_LINEAR;

	component.texGen[i] = type[i];
	component.texGen[i].SetPlane( planes[i][j] );
}

void glTexcoordGenerator::SetPlane( Renderer::TextureComponent& component, GLenum coord, GLenum pname, const GLfloat* param )
{
	const Dictionary<GLint, TexcoordFunc> table
	{
		{ GL_EYE_PLANE, TexcoordFunc::EyeLinear },
		{ GL_OBJECT_PLANE, TexcoordFunc::ObjectLinear },
	};

	const int i = GetCoordIndex( coord );
	const int j = (pname == GL_EYE_PLANE) ? 0 : 1;

	planes[i][j] = Vector4( param );
	if ( type[i] == table[pname] )
	{
		component.texGen[i].SetPlane( planes[i][j] );
	}
}