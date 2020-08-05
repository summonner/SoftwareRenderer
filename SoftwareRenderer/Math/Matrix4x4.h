#pragma once
#include "framework.h"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Radian.h"

class Matrix4x4 final
{
public:
	Matrix4x4()
		: Matrix4x4( identity )
	{
	}

	Matrix4x4(  const float m00, const float m01, const float m02, const float m03,
				const float m10, const float m11, const float m12, const float m13,
				const float m20, const float m21, const float m22, const float m23,
				const float m30, const float m31, const float m32, const float m33 )
		: m00( m00 ), m01( m01 ), m02( m02 ), m03( m03 )
		, m10( m10 ), m11( m11 ), m12( m12 ), m13( m13 )
		, m20( m20 ), m21( m21 ), m22( m22 ), m23( m23 )
		, m30( m30 ), m31( m31 ), m32( m32 ), m33( m33 )
	{
	}

	Matrix4x4( const Vector4& col0, const Vector4& col1, const Vector4& col2, const Vector4& col3 )
		: Matrix4x4(  col0.x, col1.x, col2.x, col3.x
					, col0.y, col1.y, col2.y, col3.y
					, col0.z, col1.z, col2.z, col3.z
					, col0.w, col1.w, col2.w, col3.w )
	{
	}

	inline Vector4 operator *( const Vector4& v ) const
	{
		return Vector4( v.Dot( Row0() ), v.Dot( Row1() ), v.Dot( Row2() ), v.Dot( Row3() ) );
	}

	static friend inline Vector4 operator *( const Vector4& v, const Matrix4x4& m );

	inline Matrix4x4 operator *( const Matrix4x4& m ) const
	{
		auto r0 = Row0(), r1 = Row1(), r2 = Row2(), r3 = Row3();
		auto c0 = m.Col0(), c1 = m.Col1(), c2 = m.Col2(), c3 = m.Col3();
		return Matrix4x4(
			r0.Dot( c0 ), r0.Dot( c1 ), r0.Dot( c2 ), r0.Dot( c3 ),
			r1.Dot( c0 ), r1.Dot( c1 ), r1.Dot( c2 ), r1.Dot( c3 ),
			r2.Dot( c0 ), r2.Dot( c1 ), r2.Dot( c2 ), r2.Dot( c3 ),
			r3.Dot( c0 ), r3.Dot( c1 ), r3.Dot( c2 ), r3.Dot( c3 )
		);
	}

	inline Matrix4x4 Transpose() const
	{
		return Matrix4x4(
			m00, m10, m20, m30,
			m01, m11, m21, m31,
			m02, m12, m22, m32,
			m03, m13, m23, m33
		);
	}

	static const Matrix4x4 identity;

	inline static Matrix4x4 Translate( const Vector3& displacement )
	{
		return Matrix4x4(
			1.f, 0.f, 0.f, displacement.x,
			0.f, 1.f, 0.f, displacement.y,
			0.f, 0.f, 1.f, displacement.z,
			0.f, 0.f, 0.f, 1.f
		);
	}

	inline static Matrix4x4 Scale( const Vector3& ratio )
	{
		return Matrix4x4(
			ratio.x, 0.f, 0.f, 0.f,
			0.f, ratio.y, 0.f, 0.f,
			0.f, 0.f, ratio.z, 0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	inline static Matrix4x4 Rotate( Radian angle, const Vector3& v )
	{
		auto c = cos( angle );
		auto s = sin( angle );
		auto t = 1 - c;
		auto w = v.Normalize();

		return Matrix4x4(
			w.x * w.x * t + c,			w.x * w.y * t + w.z * s,	w.x * w.z * t - w.y * s,	0.0f,
			w.y * w.x * t - w.z * s,	w.y * w.y * t + c,			w.y * w.z * t + w.x * s,	0.0f,
			w.z * w.x * t + w.y * s,	w.z * w.y * t - w.x * s,	w.z * w.z * t + c,			0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

private:
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;

#define DECL_ROW(i) inline const Vector4 Row##i() const { return Vector4( m##i##0, m##i##1, m##i##2, m##i##3 ); }
	DECL_ROW( 0 );
	DECL_ROW( 1 );
	DECL_ROW( 2 );
	DECL_ROW( 3 );

#define DECL_COL(i) inline const Vector4 Col##i() const { return Vector4( m0##i, m1##i, m2##i, m3##i ); }
	DECL_COL( 0 );
	DECL_COL( 1 );
	DECL_COL( 2 );
	DECL_COL( 3 );
};

static inline Vector4 operator *( const Vector4& v, const Matrix4x4& m )
{
	return Vector4( v.Dot( m.Col0() ), v.Dot( m.Col1() ), v.Dot( m.Col2() ), v.Dot( m.Col3() ) );
}