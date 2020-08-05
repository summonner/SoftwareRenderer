#include "framework.h"
#include "Matrix4x4.h"

const Matrix4x4 Matrix4x4::identity = Matrix4x4(
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f );