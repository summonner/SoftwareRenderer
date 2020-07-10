#pragma once
#include "Vector.h"

template<typename T>
class TVector2
{
public:
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

	inline T SquaredDistance( const TVector2& other ) const
	{
		return ((*this) - other).Dot();
	}

	inline T Dot() const
	{
		return x * x
			 + y * y;
	}

public:
	T x;
	T y;
};