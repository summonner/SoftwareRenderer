#include "framework.h"
#include "StencilOp.h"

namespace Renderer
{
	StencilOp::StencilOp()
		: func( table[Type::Keep] )
	{
	}

	StencilOp::~StencilOp()
	{
	}

	void StencilOp::operator =( Type type )
	{
		func = table[type];
	}

	StencilValue StencilOp::operator ()( StencilValue current, StencilValue ref ) const
	{
		return func( current, ref );
	}

	const Dictionary<StencilOp::Type, StencilOp::Func> StencilOp::table
	{
		{ Type::Keep, Keep },
		{ Type::Zero, Zero },
		{ Type::Replace, Replace },
		{ Type::Increase, Increase },
		{ Type::IncreaseWrap, IncreaseWrap },
		{ Type::Decrease, Decrease },
		{ Type::DecreaseWrap, DecreaseWrap },
		{ Type::Invert, Invert },
	};

	StencilValue StencilOp::Keep( StencilValue current, StencilValue ref )
	{
		return current;
	}

	StencilValue StencilOp::Zero( StencilValue current, StencilValue ref )
	{
		return 0;
	}

	StencilValue StencilOp::Replace( StencilValue current, StencilValue ref )
	{
		return ref;
	}

	StencilValue StencilOp::Increase( StencilValue current, StencilValue ref )
	{
		if ( current < std::numeric_limits<StencilValue>::max() )
		{
			++current;
		}

		return current;
	}

	StencilValue StencilOp::IncreaseWrap( StencilValue current, StencilValue ref )
	{
		if ( current < std::numeric_limits<StencilValue>::max() )
		{
			++current;
		}
		else
		{
			current = std::numeric_limits<StencilValue>::min();
		}

		return current;
	}

	StencilValue StencilOp::Decrease( StencilValue current, StencilValue ref )
	{
		if ( current > std::numeric_limits<StencilValue>::min() )
		{
			--current;
		}

		return current;
	}

	StencilValue StencilOp::DecreaseWrap( StencilValue current, StencilValue ref )
	{
		if ( current > std::numeric_limits<StencilValue>::min() )
		{
			--current;
		}
		else
		{
			current = std::numeric_limits<StencilValue>::max();
		}

		return current;
	}

	StencilValue StencilOp::Invert( StencilValue current, StencilValue ref )
	{
		return ~current;
	}

}