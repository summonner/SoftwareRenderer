#pragma once
#include "Util/Dictionary.hpp"

namespace Renderer
{
	class WrapMode final
	{
	public:
		enum class Type
		{
			_,
			Clamp,
			Repeat,
			MirroredRepeat,
		};

		WrapMode();
		~WrapMode();

		float operator ()( const float v ) const;
		void operator =( WrapMode::Type type );

	private:
		static float Clamp( float v );
		static float Repeat( float v );
		static float MirroredRepeat( float v );

		using WrapFunc = std::function<float( float )>;
		const static Dictionary<WrapMode::Type, WrapFunc> table;

		WrapFunc current;
	};
}

using TextureWrapMode = Renderer::WrapMode::Type;