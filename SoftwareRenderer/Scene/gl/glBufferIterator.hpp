#pragma once
#include "Util/IBaseIterator.h"

template<typename Output>
class IBuffer;

template<typename Output>
class BufferIterator : public IBaseIterator<BufferIterator<Output>, Output>
{
public:
	BufferIterator( const IBuffer<Output>& buffer, const int count )
		: BufferIterator( buffer, count, 0 )
	{
	}

	BufferIterator( const IBuffer<Output>& buffer, const int count, const int current )
		: buffer( buffer )
		, count( count )
		, current( current )
	{
	}

	~BufferIterator()
	{
	}

	Output operator *() const
	{
		assert( current >= 0 && current < count );
		return buffer[current];
	}

	bool operator ==( const BufferIterator& other ) const
	{
		return current == other.current;
	}

	bool operator !=( const BufferIterator& other ) const
	{
		return !(*this == other);
	}

	const BufferIterator& operator++()
	{
		++current;
		return *this;
	}

	void operator =( const BufferIterator& other )
	{
		current = other.current;
	}

	BufferIterator begin() const
	{
		if ( current == 0 )
		{
			return *this;
		}
		else
		{
			return BufferIterator( buffer, count, 0 );
		}
	}

	BufferIterator end() const
	{
		return BufferIterator( buffer, count, count );
	}

private:
	const IBuffer<Output>& buffer;
	const int count;
	int current;
};

