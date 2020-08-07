#pragma once
#include "glAdapter.h"

template<typename Output>
class IBuffer abstract
{
public:
	virtual Output operator[]( int i ) const abstract;
};

template<typename Input, typename Output>
class glBuffer final : public IBuffer<Output>
{
public:
	glBuffer( GLint size, GLenum type, GLsizei stride, const void* pointer )
		: glBuffer( size, type, stride, pointer, Output() )
	{
	}

	glBuffer( GLint size, GLenum type, GLsizei stride, const void* pointer, const Output defaultValue )
		: size( size )
		, type( type )
		, stride( stride ? stride : size * sizeof( Input ) )
		, pointer( static_cast<const BYTE*>(pointer) )
		, defaultValue( defaultValue )
	{
	}

	~glBuffer()
	{
	}

	Output operator[]( int i ) const
	{
		Output output = defaultValue;
		GetValues( i * stride, sizeof( Output ) / sizeof( Input ), (void*)&output );
		return output;
	}

private:
	void GetValues( const int index, int numCoordinates, void* outValues ) const
	{
		const auto num = std::min( numCoordinates, size );
		auto out = static_cast<Input*>(outValues);
		for ( auto i = 0; i < num; ++i )
		{
			out[i] = *((const Input*)(pointer + index) + i);
		}
	}

private:
	const GLint size;
	const GLenum type;
	const GLsizei stride;
	const BYTE* const pointer;
	const Output defaultValue;
};

