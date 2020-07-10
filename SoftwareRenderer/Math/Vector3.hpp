#pragma once
#include "Vector.h"
#include "framework.h"

template<typename T>
class TVector3
{
public:
	TVector3( const TVector2& v, T z )
		: x( v.x )
		, y( v.y )
		, z( z )
	{
	}

	TVector3( T x, T y, T z )
		: x( x )
		, y( y )
		, z( z )
	{
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

	inline TVector3 operator -( const TVector3& other ) const
	{
		return (*this) + other * -1;
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

	inline T SquaredDistance( const TVector3& other ) const
	{
		return ((*this) - other).Dot();
	}

	inline T Dot() const
	{
		return x * x
			 + y * y
			 + z * z;
	}

	inline float Length() const
	{
		return sqrt( Dot() );
	}

public:
	T x;
	T y;
	T z;
};

