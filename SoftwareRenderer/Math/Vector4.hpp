#pragma once
#include "Vector.h"
#include "framework.h"

template<typename T>
class TVector4
{
public:
	TVector4( const TVector3& v, T z )
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
		return ((*this) - other).Dot();
	}

	inline T Dot() const
	{
		return x * x
			 + y * y
			 + z * z
			 + w * w;
	}

	inline float Length() const
	{
		return sqrt( Dot() );
	}

public:
	T x, y, z, w;
};

