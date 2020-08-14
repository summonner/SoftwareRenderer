#pragma once
#include "StencilValue.h"

namespace Renderer
{
	class StencilFunc final
	{
	public:
		enum class Type
		{
			Never,
			Less,
			LEqual,
			Greater,
			GEqual,
			Equal,
			NotEqual,
			Always,
		};

	public:
		StencilFunc();
		StencilFunc( Type type, StencilValue readMask );
		~StencilFunc();

		bool operator ()( StencilValue ref, StencilValue stencil ) const;

	private:
		using Func = std::function<bool( StencilValue ref, StencilValue stencil )>;
		Func func;
		int mask;

	private:
		static const Dictionary<Type, Func> table;
		static bool Never( StencilValue ref, StencilValue stencil );
		static bool Less( StencilValue ref, StencilValue stencil );
		static bool LEqual( StencilValue ref, StencilValue stencil );
		static bool Greater( StencilValue ref, StencilValue stencil );
		static bool GEqual( StencilValue ref, StencilValue stencil );
		static bool Equal( StencilValue ref, StencilValue stencil );
		static bool NotEqual( StencilValue ref, StencilValue stencil );
		static bool Always( StencilValue ref, StencilValue stencil );
	};
}
