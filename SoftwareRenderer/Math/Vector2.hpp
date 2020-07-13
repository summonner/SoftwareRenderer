#pragma once
#include "Vector.h"

template<typename T>
class TVector2 final
{
public:
	TVector2()
		: TVector2( T( 0 ), T( 0 ) )
	{
	}

	TVector2( float x, float y )
		: TVector2( T( x ), T( y ) )
	{
	}

	TVector2( T x, T y )
		: x( x )
		, y( y )
	{
	}

	inline bool operator !=( const TVector2& other ) const
	{
		return x != other.x
			|| y != other.y;
	}

	inline TVector2 operator +( const TVector2& other ) const
	{
		return TVector2( x + other.x, y + other.y );
	}

	inline TVector2 operator -( const TVector2& other ) const
	{
		return (*this) + other * -1;
	}

	inline TVector2 operator *( const int scalar ) const
	{
		return TVector2( x * scalar, y * scalar );
	}

	inline TVector2 operator *( const float scalar ) const
	{
		return TVector2( x * scalar, y * scalar );
	}

	inline float SquaredDistance( const TVector2& other ) const
	{
		auto diff = ((*this) - other);
		return diff.Dot( diff );
	}

	inline float Dot( const TVector2& other ) const
	{
		return float( x * other.x
					+ y * other.y );
	}

public:
	T x;
	T y;
};