#include "framework.h"
#include "Matrix4x4.h"

const Matrix4x4 Matrix4x4::identity = Matrix4x4(
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f );


static inline Vector4 operator *( const Vector4& v, const Matrix4x4& m )
{
	return Vector4( v.Dot( m.Col0() ), v.Dot( m.Col1() ), v.Dot( m.Col2() ), v.Dot( m.Col3() ) );
}