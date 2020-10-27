#include "framework.h"
#include "DepthFunc.h"

namespace Renderer
{
	const Dictionary<DepthFunc::Type, DepthFunc::Func> DepthFunc::table (
	{
		{ Type::Never, Never },
		{ Type::Less, Less },
		{ Type::Equal, Equal },
		{ Type::LEqual, LEqual },
		{ Type::Greater, Greater },
		{ Type::NotEqual, NotEqual },
		{ Type::GEqual, GEqual },
		{ Type::Always, Always },
	}, Less );

	DepthFunc::DepthFunc()
		: current( Less )
	{
	}

	DepthFunc::~DepthFunc()
	{
	}

	bool DepthFunc::operator()( const float incoming, const float stored ) const
	{
		return current( incoming, stored );
	}

	void DepthFunc::operator =( const Type type )
	{
		current = table[type];
	}

	bool DepthFunc::Never( const float incoming, const float stored )
	{
		return false;
	}

	bool DepthFunc::Less( const float incoming, const float stored )
	{
		return incoming < stored;
	}

	bool DepthFunc::Equal( const float incoming, const float stored )
	{
		return abs( incoming - stored ) <= FLT_EPSILON;
	}

	bool DepthFunc::LEqual( const float incoming, const float stored )
	{
		return incoming - stored <= FLT_EPSILON;
	}

	bool DepthFunc::Greater( const float incoming, const float stored )
	{
		return incoming > stored;
	}

	bool DepthFunc::NotEqual( const float incoming, const float stored )
	{
		return abs( incoming - stored ) > FLT_EPSILON;
	}

	bool DepthFunc::GEqual( const float incoming, const float stored )
	{
		return incoming - stored >= -FLT_EPSILON;
	}

	bool DepthFunc::Always( const float incoming, const float stored )
	{
		return true;
	}
}