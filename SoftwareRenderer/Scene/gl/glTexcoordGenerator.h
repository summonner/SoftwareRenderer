#pragma once
#include "glAdapter.h"
#include "Math/Vector4.hpp"

class glTexcoordGenerator final
{
public:
	glTexcoordGenerator();
	~glTexcoordGenerator();

	void SetMode( Renderer::TextureComponent& component, GLenum coord, GLint params );
	void SetPlane( Renderer::TextureComponent& component, GLenum coord, GLenum pname, const GLfloat* params );

private:
	inline static int GetCoordIndex( GLenum coord )
	{
		return coord - GL_S;
	}

private:
	Vector4 planes[4][3]
	{
		{ Vector4( 1, 0, 0, 0 ), Vector4( 1, 0, 0, 0 ), Vector4( 1, 0, 0, 0 ) },
		{ Vector4( 0, 1, 0, 0 ), Vector4( 0, 1, 0, 0 ), Vector4( 0, 1, 0, 0 ) },
		{ Vector4( 0, 0, 0, 0 ), Vector4( 0, 0, 0, 0 ), Vector4( 0, 0, 0, 0 ) },
		{ Vector4( 0, 0, 0, 0 ), Vector4( 0, 0, 0, 0 ), Vector4( 0, 0, 0, 0 ) },
	};

	TexcoordFunc type[4]
	{
		TexcoordFunc::EyeLinear,
		TexcoordFunc::EyeLinear, 
		TexcoordFunc::EyeLinear, 
		TexcoordFunc::EyeLinear
	};
};

