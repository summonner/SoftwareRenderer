#pragma once
#include "Vector.h"

template<typename T>
class TVector4 final
{
public:
	TVector4( const TVector3<T>& v, T z )
		: x( v.x )
		, y( v.y )
		, z( v.z )
		, w( w )
	{
	}

	TVector4( T x, T y, T z, T w )
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

	inline TVector4 operator *( const int scalar ) const
	{
		return TVector4( x * scalar, y * scalar, z * scalar, w * scalar );
	}

	inline TVector4 operator *( const float scalar ) const
	{
		return TVector4( x * scalar, y * scalar, z * scalar, w * scalar );
	}

	inline TVector4 operator /( const float scalar ) const
	{
		return (*this) * (1.f / scalar);
	}

	inline T SquaredDistance( const TVector4& other ) const
	{
		TVector4 diff = ((*this) - other);
		return diff.Dot( diff );
	}

	inline T Dot( const TVector4& other ) const
	{
		return x * other.x
			 + y * other.y
			 + z * other.z
			 + w * other.w;
	}

	inline float Length() const
	{
		return sqrt( this->Dot( *this ) );
	}

	inline float Normalize() const
	{
		return *this / Length();
	}

public:
	T x, y, z, w;
};

template<typename T>
static inline TVector4<T> operator *( const float scalar, const TVector4<T>& vector )
{
	return vector * scalar;
}