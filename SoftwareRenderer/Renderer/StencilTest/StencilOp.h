#pragma once
#include "StencilValue.h"

namespace Renderer
{
	class StencilOp final
	{
	public:
		enum class Type
		{
			Keep,
			Zero,
			Replace,
			Increase,
			IncreaseWrap,
			Decrease,
			DecreaseWrap,
			Invert,
		};

	public:
		StencilOp();
		~StencilOp();

		void operator =( Type type );
		StencilValue operator ()( StencilValue current, StencilValue ref ) const;

	private:
		using Func = std::function<StencilValue( StencilValue current, StencilValue ref )>;
		Func func;

	private:
		static const Dictionary<Type, Func> table;
		static StencilValue Keep( StencilValue current, StencilValue ref );
		static StencilValue Zero( StencilValue current, StencilValue ref );
		static StencilValue Replace( StencilValue current, StencilValue ref );
		static StencilValue Increase( StencilValue current, StencilValue ref );
		static StencilValue IncreaseWrap( StencilValue current, StencilValue ref );
		static StencilValue Decrease( StencilValue current, StencilValue ref );
		static StencilValue DecreaseWrap( StencilValue current, StencilValue ref );
		static StencilValue Invert( StencilValue current, StencilValue ref );
	};
}

using StencilOp = Renderer::StencilOp::Type;