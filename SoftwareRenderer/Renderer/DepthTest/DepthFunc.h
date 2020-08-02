#pragma once

namespace Renderer
{
	class DepthFunc final
	{
	public:
		enum class Type
		{
			Never,
			Less,
			Equal,
			LEqual,
			Greater,
			NotEqual,
			GEqual,
			Always,
		};

	public:
		DepthFunc();
		~DepthFunc();

		bool operator ()( float incoming, float stored ) const;
		void operator =( Type type );

	private:
		using Func = std::function<bool( float, float )>;
		Func current;

		static const Dictionary<Type, Func> table;
		static bool Never( float incoming, float stored );
		static bool Less( float incoming, float stored );
		static bool Equal( float incoming, float stored );
		static bool LEqual( float incoming, float stored );
		static bool Greater( float incoming, float stored );
		static bool NotEqual( float incoming, float stored );
		static bool GEqual( float incoming, float stored );
		static bool Always( float incoming, float stored );
	};
}

using DepthFunc = Renderer::DepthFunc::Type;