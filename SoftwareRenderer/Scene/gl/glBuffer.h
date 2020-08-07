#pragma once
#include "glAdapter.h"

class glBuffer
{
public:
	glBuffer( GLint size, GLenum type, GLsizei stride, const void* pointer );
	~glBuffer();

	Vector4 GetVector4( const int index ) const;
	Vector3 GetVector3( const int index ) const;
	Vector2 GetVector2( const int index ) const;

private:
	void GetValues( const int index, int size, float outValues[] ) const;

private:
	const GLint size;
	const GLenum type;
	const GLsizei stride;
	const BYTE* const pointer;
};

