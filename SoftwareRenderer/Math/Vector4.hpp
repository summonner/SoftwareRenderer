#pragma once
#include "Vector.h"

template<typename T>
class TVector4 final
{
public:
	constexpr TVector4()
		: TVector4( T( 0 ), T( 0 ), T( 0 ), T( 0 ) )
	{
	}

	constexpr TVector4( const TVector3<T>& v, T w )
		: TVector4( T( v.x ), T( v.y ), T( v.z ), w )
	{
	}

	constexpr TVector4( T x, T y, T z, T w )
		: x( x )
		, y( y )
		, z( z )
		, w( w )
	{
	}

	inline bool operator ==( const TVector4& other ) const
	{
		return x == other.x
			&& y == other.y
			&& z == other.z
			&& w == other.w;
	}

	inline bool operator !=( const TVector4& other ) const
	{
		return !((*this) == other);
	}

	inline TVector4 operator +( const TVector4& other ) const
	{
		return TVector4( x + other.x, y + other.y, z + other.z, w + other.w );
	}

	inline TVector4 operator -( const TVector4& other ) const
	{
		return (*this) + other * -1;
	}

	inline TVector4 operator -() const
	{
		return *this * -1;
	}

	inline TVector4 operator *( const int scalar ) const
	{
		return TVector4( x * scalar, y * scalar, z * scalar, w * scalar );
	}

	inline TVector4 operator *( const float scalar ) const
	{
		return TVector4( x * scalar, y * scalar, z * scalar, w * scalar );
	}

	inline TVector4 operator *( const TVector4& other ) const
	{
		return TVector4( x * other.x, y * other.y, z * other.z, w * other.w );
	}

	inline TVector4 operator /( const float scalar ) const
	{
		return (*this) * (1.f / scalar);
	}

	inline void operator +=( const TVector4& other )
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
	}

	inline void operator -=( const TVector4& other )
	{
		*this += -other;
	}

	inline void operator *=( const float scalar )
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
	}

	inline void operator /=( const float scalar )
	{
		*this *= 1.f / scalar;
	}

	inline void operator *=( const TVector4& other )
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
	}

	inline void operator /=( const TVector4& other )
	{
		*this *= 1.f / other;
	}

	inline float SquaredDistance( const TVector4& other ) const
	{
		TVector4 diff = ((*this) - other);
		return diff.Dot( diff );
	}

	inline float Dot( const TVector4& other ) const
	{
		return float( x * other.x
					+ y * other.y
					+ z * other.z
					+ w * other.w );
	}

	inline float Length() const
	{
		return sqrt( this->Dot( *this ) );
	}

	inline float Normalize() const
	{
		return *this / Length();
	}

	static TVector4 Lerp( const TVector4& left, const TVector4& right, const float t );
	static const TVector4<T> zero;
	static const TVector4<T> one;

public:
	T x, y, z, w;
};

template<typename T>
static inline TVector4<T> operator *( const float scalar, const TVector4<T>& vector )
{
	return vector * scalar;
}

template<typename T>
TVector4<T> TVector4<T>::Lerp( const TVector4<T>& start, const TVector4<T>& end, const float t )
{
	return start * (1.f - t) + end * t;
}

template<typename T>
const TVector4<T> TVector4<T>::zero = TVector4<T>( T( 0 ), T( 0 ), T( 0 ), T( 0 ) );

template<typename T>
const TVector4<T> TVector4<T>::one = TVector4<T>( T( 1 ), T( 1 ), T( 1 ), T( 1 ) );