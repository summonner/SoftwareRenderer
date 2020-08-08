#pragma once
#include "../glAdapter.h"

template<typename Output>
class IBuffer abstract
{
public:
	virtual Output operator[]( int i ) const abstract;
};

template<typename Input, typename Output>
class glBuffer final : public IBuffer<typename Output::Output>
{
public:
	glBuffer( GLint size, GLsizei stride, const void* pointer )
		: size( size )
		, stride( stride ? stride : size * sizeof( Input ) )
		, pointer( static_cast<const BYTE*>(pointer) )
	{
	}

	~glBuffer()
	{
	}

	typename Output::Output operator[]( int i ) const
	{
		typename Output::Output output = Output::defaultValue;
		GetValues( i * stride, sizeof( typename Output::Output ) / sizeof( typename Output::Subtype ), (void*)&output );
		return output;
	}

private:
	void GetValues( const int index, int numCoordinates, void* outValue ) const
	{
		const auto num = std::min( numCoordinates, size );
		auto outSubValues = static_cast<typename Output::Subtype*>(outValue);
		const auto values = (const Input*)(pointer + index);
		for ( auto i = 0; i < num; ++i )
		{
			outSubValues[i] = (typename Output::Subtype)(values[i]);
		}
	}

private:
	const GLint size;
	const GLsizei stride;
	const BYTE* const pointer;

};

class glBufferFactory final abstract
{
public:
	template<typename Output>
	static std::unique_ptr<IBuffer<typename Output::Output>> Create( GLint size, GLenum type, GLsizei stride, const GLvoid* pointer )
	{
		switch ( type )
		{
		case GL_BYTE:
			return std::make_unique<glBuffer<char, Output>>( size, stride, pointer );
		case GL_UNSIGNED_BYTE:
			return std::make_unique<glBuffer<BYTE, Output>>( size, stride, pointer );
		case GL_SHORT:
			return std::make_unique<glBuffer<short, Output>>( size, stride, pointer );
		case GL_UNSIGNED_SHORT:
			return std::make_unique<glBuffer<unsigned short, Output>>( size, stride, pointer );
		case GL_INT:
			return std::make_unique<glBuffer<int, Output>>( size, stride, pointer );
		case GL_UNSIGNED_INT:
			return std::make_unique<glBuffer<unsigned int, Output>>( size, stride, pointer );
		case GL_DOUBLE:
			return std::make_unique<glBuffer<double, Output>>( size, stride, pointer );
		default:
		case GL_FLOAT:
			return std::make_unique<glBuffer<float, Output>>( size, stride, pointer );
		}
	}
};