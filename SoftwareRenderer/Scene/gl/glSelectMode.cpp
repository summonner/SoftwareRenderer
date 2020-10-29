#include "framework.h"
#include "glSelectMode.h"
#include "Renderer/Rasterizer/IRasterizer.h"

glSelectMode::glSelectMode()
	: enabled( false )
	, nameStack()
	, buffer( 0, nullptr )
	, record()
{
}

glSelectMode::~glSelectMode()
{
}

int glSelectMode::SetEnable( bool enable )
{
	enabled = enable;

	ResetRecord();
	return buffer.Reset();
}

bool glSelectMode::IsEnabled() const
{
	return enabled;
}

void glSelectMode::SetBuffer( GLsizei size, GLuint* buffer )
{
	this->buffer = Buffer( size, buffer );
}

void glSelectMode::InitNames()
{
	if ( enabled == false )
	{
		return;
	}

	while ( nameStack.size() > 0 )
	{
		nameStack.pop();
	}
	ResetRecord();
}

void glSelectMode::PushName( GLuint name )
{
	if ( enabled == false )
	{
		return;
	}

	nameStack.push( name );
	ResetRecord();
}

void glSelectMode::PopName()
{
	if ( enabled == false )
	{
		return;
	}

	nameStack.pop();
	ResetRecord();
}

void glSelectMode::LoadName( GLuint name )
{
	if ( enabled == false )
	{
		return;
	}

	nameStack.pop();
	nameStack.push( name );
	ResetRecord();
}

void glSelectMode::ResetRecord()
{
	if ( record.IsHit() == true )
	{
		buffer.Push( record );
	}
	record.Reset();
}

void glSelectMode::OnRasterize( const Renderer::IRasterizer& rasterizer, const Bounds& bounds )
{
	record.Hit( nameStack, rasterizer.Selection() );
}


glSelectMode::Buffer::Buffer( GLsizei size, GLuint* buffer )
	: maxSize( size / 4 )
	, container( buffer )
	, current( 0 )
{
}

void glSelectMode::Buffer::Push( const HitRecord& record )
{
	if ( current >= maxSize )
	{
		return;
	}

	memcpy( container + current * 4, &record, sizeof( GLuint ) * 4 );
	++current;
}

int glSelectMode::Buffer::Reset()
{
	const auto backup = current;
	current = 0;
	return backup;
}

void glSelectMode::HitRecord::Reset()
{
	numStack = 0;
	near = UINT_MAX;
	far = 0;
	name = 0;
}

void glSelectMode::HitRecord::Hit( const std::stack<GLuint>& stack, const std::pair<float, float>& range )
{
	auto min = (GLuint)((range.first + 1.f) * 0.5f * UINT_MAX);
	auto max = (GLuint)((range.second + 1.f) * 0.5f * UINT_MAX);
	near = std::min( min, near );
	far = std::max( max, far );

	numStack = stack.size();
	name = stack.top();
}

bool glSelectMode::HitRecord::IsHit() const
{
	return near <= far;
}