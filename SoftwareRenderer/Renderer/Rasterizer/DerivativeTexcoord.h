#pragma once
#include "Math/Vector2.hpp"

namespace Renderer
{
	class Vertex;
	class DerivativeTexcoord final
	{
	private:
		DerivativeTexcoord();
		DerivativeTexcoord( const Vector2& dw, const Vector2& ddx, const Vector2& ddy );
	public:
		static DerivativeTexcoord Line( const Vertex& a, const Vertex& b );
		static DerivativeTexcoord Triangle( const Vertex& a, const Vertex& b, const Vertex& c );
		~DerivativeTexcoord();

		Vector2 dFdx( const Vector2& texcoord, const float w ) const;
		Vector2 dFdy( const Vector2& texcoord, const float w ) const;

		inline bool IsValid() const
		{
			return isValid;
		}

		static const DerivativeTexcoord invalid;

	private:
		const Vector2 dw;
		const Vector2 ddx, ddy;
		const bool isValid;
	};
}