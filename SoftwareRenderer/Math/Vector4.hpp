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

	constexpr TVector4( const T values[] )
		: TVector4( values[0], values[1], values[2], values[3] )
	{
	}

	constexpr TVector4( T x, T y, T z, T w )
		: x( x )
		, y( y )
		, z( z )
		, w( w )
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
		case 3:
			return w;
		default:
			assert( "invalid range" && false );
			return x;
		}
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

	inline TVector4 operator +( T scalar ) const
	{
		return (*this) + TVector4::one * scalar;
	}

	inline TVector4 operator -( const TVector4& other ) const
	{
		return (*this) + other * -1;
	}

	inline TVector4 operator -( T scalar ) const
	{
		return (*this) + -scalar;
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

	inline void operator +=( T scalar )
	{
		(*this) += TVector4::one * scalar;
	}

	inline void operator -=( const TVector4& other )
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
		w *= scalar;
	}

	inline void operator /=( const float scalar )
	{
		(*this) *= 1.f / scalar;
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
		(*this) *= 1.f / other;
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

	inline TVector3<T> Normalize3() const
	{
		return TVector3<T>( *this ).Normalize();
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

inline Vector4 Clamp( const Vector4& v )
{
	return Vector4(
		std::clamp( v.x, 0.f, 1.f ),
		std::clamp( v.y, 0.f, 1.f ),
		std::clamp( v.z, 0.f, 1.f ),
		std::clamp( v.w, 0.f, 1.f )
	);
}