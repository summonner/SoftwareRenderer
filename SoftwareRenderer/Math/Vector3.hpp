#pragma once
#include "Vector.h"
#include "framework.h"

template<typename T>
class TVector3 final
{
public:
	TVector3()
		: TVector3( T( 0 ), T( 0 ), T( 0 ) )
	{
	}

	TVector3( const TVector2<T>& v, T z )
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
		return *this / Length();
	}

	inline TVector3 Cross( const TVector3& other ) const
	{
		return TVector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	//inline static const TVector3 left =  TVector3( T( 1), T( 0), T( 0) );
	//inline static const TVector3 right = TVector3( T(-1), T( 0), T( 0) );
	//inline static const TVector3 up =	  TVector3( T( 0), T( 1), T( 0) );
	//inline static const TVector3 down =  TVector3( T( 0), T(-1), T( 0) );
	//inline static const TVector3 front = TVector3( T( 0), T( 0), T( 1) );
	//inline static const TVector3 back =  TVector3( T( 0), T( 0), T(-1) );

public:
	T x;
	T y;
	T z;
};

template<typename T>
inline TVector3<T> operator *( T scalar, const TVector3<T>& vector )
{
	return vector * scalar;
}