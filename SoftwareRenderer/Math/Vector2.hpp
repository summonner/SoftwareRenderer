#pragma once
#include "Vector.h"

template<typename T>
class TVector2 final
{
public:
	constexpr TVector2()
		: TVector2( T( 0 ), T( 0 ) )
	{
	}

	constexpr TVector2( const TVector2<int>& v )
		: TVector2( T( v.x ), T( v.y ) )
	{
	}

	constexpr TVector2( const TVector2<float>& v )
		: TVector2( T( v.x ), T( v.y ) )
	{
	}

	constexpr TVector2( const TVector3<T>& v )
		: TVector2( T( v.x ), T( v.y ) )
	{
	}

	constexpr TVector2( T x, T y )
		: x( x )
		, y( y )
	{
	}

	inline T& operator[]( int i )
	{
		switch ( i )
		{
		case 0:
			return x;
		case 1:
			return y;
		default:
			assert( "invalid range" && false );
			return x;
		}
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

	inline TVector2 operator +( T scalar ) const
	{
		return (*this) + TVector2::one * scalar;
	}

	inline TVector2 operator -( T scalar ) const
	{
		return (*this) + -scalar;
	}

	inline TVector2 operator *( const int scalar ) const
	{
		return TVector2( x * scalar, y * scalar );
	}

	inline TVector2 operator *( const float scalar ) const
	{
		return TVector2( T(x * scalar), T(y * scalar) );
	}

	inline TVector2 operator *( const TVector2& other ) const
	{
		return TVector2( x * other.x, y * other.y );
	}

	inline TVector2 operator /( const float scalar ) const
	{
		return (*this) * (1.f / scalar);
	}

	inline TVector2 operator /( const TVector2& other ) const
	{
		return TVector2( x / other.x, y / other.y );
	}

	inline void operator +=( const TVector2& other )
	{
		x += other.x;
		y += other.y;
	}

	inline void operator +=( const T scalar )
	{
		(*this) += TVector2::one * scalar;
	}

	inline void operator -=( const TVector2& other )
	{
		(*this) += -other;
	}

	inline void operator -=( const T scalar )
	{
		(*this) += -scalar;
	}

	inline void operator *=( const TVector2& other )
	{
		x *= other.x;
		y *= other.y;
	}

	inline void operator *=( const T scalar )
	{
		(*this) *= TVector2( scalar, scalar );
	}

	inline void operator /=( const TVector2& other )
	{
		x /= other.x;
		y /= other.y;
	}

	inline void operator /=( const float scalar )
	{
		x /= scalar;
		y /= scalar;
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

	inline float Length() const
	{
		return sqrt( this->Dot( *this ) );
	}

	inline TVector2 Normalize() const
	{
		if ( *this == TVector2::zero )
		{
			return *this;
		}
		else
		{
			return *this / Length();
		}
	}

	static TVector2 Lerp( const TVector2& left, const TVector2& right, const float t );
	static const TVector2<T> zero;
	static const TVector2<T> one;
	static const TVector2<T> left;
	static const TVector2<T> right;
	static const TVector2<T> up;
	static const TVector2<T> down;

public:
	T x;
	T y;
};

template<typename T>
const TVector2<T> TVector2<T>::zero = TVector2( T( 0 ), T( 0 ) );

template<typename T>
const TVector2<T> TVector2<T>::one = TVector2( T( 1 ), T( 1 ) );

template<typename T>
const TVector2<T> TVector2<T>::left = TVector2( T( -1 ), T( 0 ) );

template<typename T>
const TVector2<T> TVector2<T>::right = TVector2( T( 1 ), T( 0 ) );

template<typename T>
const TVector2<T> TVector2<T>::up = TVector2( T( 0 ), T( 1 ) );

template<typename T>
const TVector2<T> TVector2<T>::down = TVector2( T( 0 ), T( -1 ) );

template<typename T>
inline const TVector2<T> operator *( const int scalar, const TVector2<T>& vector )
{
	return vector * scalar;
}

template<typename T>
inline const TVector2<T> operator *( const float scalar, const TVector2<T>& vector )
{
	return vector * scalar;
}

template<typename T>
TVector2<T> TVector2<T>::Lerp( const TVector2<T>& start, const TVector2<T>& end, const float t )
{
	return start * (1.f - t) + end * t;
}
