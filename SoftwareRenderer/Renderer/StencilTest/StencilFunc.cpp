#include "framework.h"
#include "StencilFunc.h"

namespace Renderer
{
	StencilFunc::StencilFunc()
		: func( table[Type::Always] )
		, mask( std::numeric_limits<StencilValue>::max() )
	{
	}

	StencilFunc::StencilFunc( Type type, StencilValue mask )
		: func( table[type] )
		, mask( mask )
	{
	}

	StencilFunc::~StencilFunc()
	{
	}

	bool StencilFunc::operator ()( StencilValue ref, StencilValue stencil ) const
	{
		return func( ref & mask, stencil & mask );
	}

	const Dictionary<StencilFunc::Type, StencilFunc::Func> StencilFunc::table
	{
		{ Type::Never, Never },
		{ Type::Less, Less },
		{ Type::LEqual, LEqual },
		{ Type::Greater, Greater },
		{ Type::GEqual, GEqual },
		{ Type::Equal, Equal },
		{ Type::NotEqual, NotEqual },
		{ Type::Always, Always },
	};

	bool StencilFunc::Never( StencilValue ref, StencilValue stencil )
	{
		return false;
	}

	bool StencilFunc::Less( StencilValue ref, StencilValue stencil )
	{
		return ref < stencil;
	}

	bool StencilFunc::LEqual( StencilValue ref, StencilValue stencil )
	{
		return ref <= stencil;
	}

	bool StencilFunc::Greater( StencilValue ref, StencilValue stencil )
	{
		return ref > stencil;
	}

	bool StencilFunc::GEqual( StencilValue ref, StencilValue stencil )
	{
		return ref >= stencil;
	}

	bool StencilFunc::Equal( StencilValue ref, StencilValue stencil )
	{
		return ref == stencil;
	}

	bool StencilFunc::NotEqual( StencilValue ref, StencilValue stencil )
	{
		return ref != stencil;
	}

	bool StencilFunc::Always( StencilValue ref, StencilValue stencil )
	{
		return true;
	}
}