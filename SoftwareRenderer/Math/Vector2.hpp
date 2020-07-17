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

	TVector2( const TVector2<int>& v )
		: TVector2( T( v.x ), T( v.y ) )
	{
	}

	TVector2( const TVector2<float>& v )
		: TVector2( T( v.x ), T( v.y ) )
	{
	}

	TVector2( const TVector3<T>& v )
		: TVector2( T( v.x ), T( v.y ) )
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

	inline TVector2 operator -() const
	{
		return (*this) * -1;
	}

	inline TVector2 operator +( const TVector2& other ) const
	{
		return TVector2( x + other.x, y + other.y );
	}

	inline TVector2 operator -( const TVector2& other ) const
	{
		return (*this) + (-other);
	}

	inline TVector2 operator *( const int scalar ) const
	{
		return TVector2( x * scalar, y * scalar );
	}

	inline TVector2 operator *( const float scalar ) const
	{
		return TVector2( x * scalar, y * scalar );
	}

	inline TVector2 operator *( const TVector2& other ) const
	{
		return TVector2( x * other.x, y * other.y );
	}

	inline void operator +=( const TVector2& other )
	{
		x += other.x;
		y += other.y;
	}

	inline void operator -=( const TVector2& other )
	{
		(*this) += -other;
	}

	inline void operator *=( const float scalar )
	{
		x *= scalar;
		y *= scalar;
	}

	inline bool operator ==( const TVector2& other ) const
	{
		return x == other.x
			&& y == other.y;
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

	inline float Area( const TVector2& other ) const
	{
		return float( x * other.y
					- y * other.x );
	}

	static TVector2 Lerp( const TVector2& left, const TVector2& right, const float t );
	static const TVector2<T> zero;

public:
	T x;
	T y;
};

template<typename T>
const TVector2<T> TVector2<T>::zero = TVector2( T( 0 ), T( 0 ) );

template<typename T>
inline const TVector2<T> operator *( const int scalar, const TVector2<T>& vector )
{
	return vector * scalar;
}

template<typename T>
TVector2<T> TVector2<T>::Lerp( const TVector2<T>& start, const TVector2<T>& end, const float t )
{
	return start * (1.f - t) + end * t;
}
