#include "framework.h"
#include "glBuffer.h"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

glBuffer::glBuffer( GLint size, GLenum type, GLsizei stride, const void* pointer )
	: size( size )
	, type( type )
	, stride( stride ? stride : size * 4 )
	, pointer( static_cast<const BYTE*>( pointer ) )
{
}

glBuffer::~glBuffer()
{
}

Vector4 glBuffer::GetVector4( int index ) const
{
	float result[4] = { 0.f, 0.f, 0.f, 1.f };
	GetValues( index * stride, 4, result );
	return Vector4( result[0], result[1], result[2], result[3] );
}

Vector3 glBuffer::GetVector3( int index ) const
{
	float result[3] = { 0.f, 0.f, 0.f };
	GetValues( index * stride, 3, result );
	return Vector3( result[0], result[1], result[2] );
}

Vector2 glBuffer::GetVector2( int index ) const
{
	float result[2] = { 0.f, 0.f };
	GetValues( index * stride, 2, result );
	return Vector2( result[0], result[1] );
}

void glBuffer::GetValues( const int index, const int numCoordinates, float outValues[] ) const
{
	const auto num = std::min( numCoordinates, size );
	for ( auto i = 0; i < num; ++i )
	{
		outValues[i] = *((const float*)(pointer + index) + i);
	}
}