#pragma once
#include "Vector.h"
#include "framework.h"

template<typename T>
class TVector3 final
{
public:
	constexpr TVector3()
		: TVector3( T( 0 ), T( 0 ), T( 0 ) )
	{
	}

	constexpr TVector3( const TVector4<T>& v )
		: TVector3( T( v.x ), T( v.y ), T( v.z ) )
	{
	}

	constexpr TVector3( const TVector2<T>& v, T z )
		: TVector3( T( v.x ), T( v.y ), z )
	{
	}

	constexpr TVector3( T x, T y, T z )
		: x( x )
		, y( y )
		, z( z )
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
		case 2:
			return z;
		default:
			assert( "invalid range" && false );
			return x;
		}
	}

	inline bool operator ==( const TVector3& other ) const
	{
		return x == other.x
			&& y == other.y
			&& z == other.z;
	}

	inline bool operator !=( const TVector3& other ) const
	{
		return !((*this) == other);
	}

	inline TVector3 operator +( const TVector3& other ) const
	{
		return TVector3( x + other.x, y + other.y, z + other.z );
	}

	inline TVector3 operator +( T scalar ) const
	{
		return (*this) + TVector3::one * scalar;
	}

	inline TVector3 operator -( const TVector3& other ) const
	{
		return (*this) + other * -1;
	}

	inline TVector3 operator -( T scalar ) const
	{
		return (*this) + -scalar;
	}

	inline TVector3 operator -() const
	{
		return (*this) * -1;
	}

	inline TVector3 operator *( const int scalar ) const
	{
		return TVector3( x * scalar, y * scalar, z * scalar );
	}

	inline TVector3 operator *( const float scalar ) const
	{
		return TVector3( x * scalar, y * scalar, z * scalar );
	}

	inline TVector3 operator /( const float scalar ) const
	{
		return (*this) * (1.f / scalar);
	}

	inline void operator +=( const TVector3& other )
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}

	inline void operator +=( T scalar )
	{
		(*this) += TVector3::one * scalar;
	}

	inline void operator -=( const TVector3& other )
	{
		(*this) += -other;
	}

	inline void operator -=( T scalar )
	{
		(*this) += -scalar;
	}

	inline void operator *=( const float scalar )
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	inline void operator /=( const float scalar )
	{
		*this *= (1.f / scalar);
	}

	inline void operator *=( const TVector3& other )
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
	}

	inline void operator /=( const TVector3& other )
	{
		*this *= (1.f / other);
	}

	inline float SquaredDistance( const TVector3& other ) const
	{
		auto diff = (*this) - other;
		return diff.Dot( diff );
	}

	inline float Dot( const TVector3& other ) const
	{
		return float( x * other.x
					+ y * other.y
					+ z * other.z );
	}

	inline float Length() const
	{
		return sqrt( this->Dot( *this ) );
	}

	inline TVector3 Normalize() const
	{
		if ( *this == TVector3::zero )
		{
			return *this;
		}
		else
		{
			return *this / Length();
		}
	}

	inline TVector3 Cross( const TVector3& other ) const
	{
		return TVector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}
	
	static TVector3 Lerp( const TVector3& left, const TVector3& right, const float t );
	static const TVector3<T> zero;
	static const TVector3<T> one;

	static const TVector3<T> left;
	static const TVector3<T> right;
	static const TVector3<T> up;
	static const TVector3<T> down;
	static const TVector3<T> front;
	static const TVector3<T> back;

public:
	T x;
	T y;
	T z;
};

template<typename T>
inline TVector3<T> operator *( float scalar, const TVector3<T>& vector )
{
	return vector * scalar;
}

template<typename T>
TVector3<T> TVector3<T>::Lerp( const TVector3<T>& start, const TVector3<T>& end, const float t )
{
	return start * (1.f - t) + end * t;
}

template<typename T>
const TVector3<T> TVector3<T>::zero = TVector3<T>( T( 0 ), T( 0 ), T( 0 ) );

template<typename T>
const TVector3<T> TVector3<T>::one = TVector3<T>( T( 1 ), T( 1 ), T( 1 ) );

template<typename T>
const TVector3<T> TVector3<T>::left = TVector3( T( 1 ), T( 0 ), T( 0 ) );

template<typename T>
const TVector3<T> TVector3<T>::right = TVector3( T( -1 ), T( 0 ), T( 0 ) );

template<typename T>
const TVector3<T> TVector3<T>::up = TVector3( T( 0 ), T( 1 ), T( 0 ) );

template<typename T>
const TVector3<T> TVector3<T>::down = TVector3( T( 0 ), T( -1 ), T( 0 ) );

template<typename T>
const TVector3<T> TVector3<T>::front = TVector3( T( 0 ), T( 0 ), T( 1 ) );

template<typename T>
const TVector3<T> TVector3<T>::back = TVector3( T( 0 ), T( 0 ), T( -1 ) );