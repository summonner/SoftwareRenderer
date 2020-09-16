#include "framework.h"
#include "glDisplayListManager.h"
#include "Buffer/glBuffer.hpp"
#include "Buffer/glBufferIterator.hpp"

glDisplayListManager::glDisplayListManager()
	: displayLists()
	, base( 0 )
{
}

glDisplayListManager::~glDisplayListManager()
{
}

GLuint glDisplayListManager::Generate( GLsizei range )
{
	GLuint i = 0u;
	GLsizei num = range;
	while ( num > 0 && i < MAXUINT )
	{
		++i;
		if ( displayLists.Contains( i ) == true )
		{
			num = range;
			continue;
		}

		--num;
	}

	if ( num > 0 )
	{
		return 0;
	}

	auto r = RangeInt( i - (range - 1), i + 1 );
	for ( const auto& i : r )
	{
		displayLists.Add( i, glDisplayList() );
	}

	return r.min;
}

void glDisplayListManager::Delete( GLuint list, GLsizei range )
{
	if ( range <= 0 )
	{
		return;
	}

	for ( auto i = 0; i < range; ++i )
	{
		displayLists.Remove( i );
	}
}

void glDisplayListManager::SetBase( GLuint base )
{
	this->base = base;
}

glDisplayList* glDisplayListManager::Get( GLuint list )
{
	return &displayLists[list];
}

struct DisplayListId
{
	using Output = GLuint;
	using Subtype = GLuint;
	static constexpr Output defaultValue = 0;
};

const std::vector<const glDisplayList*> glDisplayListManager::Get( GLsizei n, GLenum type, const GLvoid* lists ) const
{
	auto buffer = glBufferFactory::Create<DisplayListId>( 1, type, 0, lists );
	BufferIterator<GLuint> iterator( *buffer, n );
	
	std::vector<const glDisplayList*> results;
	for ( auto i : iterator )
	{
		results.push_back( &displayLists[i + base] );
	}
	return results;
}