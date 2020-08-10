#pragma once

namespace Renderer
{
	class ShadeModel abstract final
	{
	public:
		using ShadeFunc = std::function<Vector4( float )>;

		enum class Type
		{
			Smooth,
			Flat,
		};

	public:
		static ShadeFunc FlatFunc( const Vector4& color );
		static ShadeFunc SmoothFunc( const Vector4& a, const Vector4& b );
		static bool IsFlat();

		static Type type;
	};
}