#include "framework.h"
#include "PolygonMode.h"


namespace Renderer
{
	PolygonMode::PolygonMode()
		: front( Mode::Fill )
		, back( Mode::Fill )
	{
		Reset();
	}

	PolygonMode::~PolygonMode()
	{
	}

	void PolygonMode::Reset()
	{
		front = Mode::Fill;
		back = Mode::Fill;
	}

	PolygonMode::Mode PolygonMode::Get( bool isFront ) const
	{
		return isFront ? front : back;
	}
}