#include "framework.h"
#include "WrapMode.h"

namespace Renderer
{
	const Dictionary<WrapMode::Type, WrapMode::WrapFunc> WrapMode::table(
	{
		{ Type::Clamp, &Clamp },
		{ Type::Repeat, &Repeat },
		{ Type::MirroredRepeat, &MirroredRepeat }
	}, &Clamp );

	float WrapMode::Clamp( float v )
	{
		return std::clamp( v, 0.f, 1.f );
	}

	float WrapMode::Repeat( float v )
	{
		return v - (int)v + (v >= 0.f ? 0 : 1);
	}

	float WrapMode::MirroredRepeat( float v )
	{
		v = v - ((int)v & ~1);
		if ( v < 0 )
		{
			v *= -1;
		}

		v = (v - 1);
		if ( v < 0 )
		{
			v *= -1;
		}
		return v;
	}

	WrapMode::WrapMode()
		: current( &Clamp )
	{
	}

	WrapMode::~WrapMode()
	{
	}

	float WrapMode::operator ()( const float v ) const
	{
		return current( v );
	}

	void WrapMode::operator =( const WrapMode::Type type )
	{
		if ( type == WrapMode::Type::_ )
		{
			return;
		}

		current = table[type];
	}
}