#include "framework.h"
#include "Matrix.h"

namespace Renderer
{
	Matrix::Matrix()
		: value( Matrix4x4::identity )
		, inverse( Matrix4x4::identity )
	{
	}

	Matrix::~Matrix()
	{
	}

	void Matrix::Reset()
	{
		value = Matrix4x4::identity;
		inverse = Matrix4x4::identity;
	}

	void Matrix::Translate( float x, float y, float z )
	{
		value *= Matrix4x4::Translate( Vector3( x, y, z ) );
		inverse = Matrix4x4::Translate( Vector3( x, y, z ) * -1 ) * inverse;
	}

	void Matrix::Rotate( Degree angle, float x, float y, float z )
	{
		const auto rotate = Matrix4x4::Rotate( angle, Vector3( x, y, z ) );
		value *= rotate;
		inverse = rotate.Transpose() * inverse;
	}

	void Matrix::Scale( float x, float y, float z )
	{
		value *= Matrix4x4::Scale( Vector3( x, y, z ) );
		inverse = Matrix4x4::Scale( Vector3( 1 / x, 1 / y, 1 / z ) ) * inverse;
	}

	void Matrix::Viewport( int left, int bottom, int width, int height )
	{
		const auto w = width * 0.5f;
		const auto h = height * 0.5f;
		const auto x = w + left + 0.5f;
		const auto y = h + bottom + 0.5f;
		value = Matrix4x4(
			w, 0, 0, x,
			0, h, 0, y,
			0, 0, 1, 0,
			0, 0, 0, 1
		);

		inverse = Matrix4x4(
			1 / w, 0, 0, -x / w,
			0, 1 / h, 0, -y / h,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	void Matrix::Frustum( float l, float r, float t, float b, float n, float f )
	{
		value *= Matrix4x4(
			2 * n / (r - l), 0, (r + l) / (r - l), 0,
			0, 2 * n / (t - b), (t + b) / (t - b), 0,
			0, 0, -(f + n) / (f - n), -2 * f * n / (f - n),
			0, 0, -1, 0
		);

		inverse = Matrix4x4(
			// TODO
		) * inverse;
	}

	void Matrix::Perspective( Degree fovY, float aspect, float near, float far )
	{
		auto halfHeight = near * tanf( Radian( fovY / 2 ) );
		auto halfWidth = halfHeight * aspect;
		Frustum( -halfWidth, halfWidth, halfHeight, -halfHeight, near, far );
		return;
	}

	void Matrix::Ortho( float l, float r, float t, float b, float n, float f )
	{
		const Vector3 scale( 2 / (r - l), 2 / (t - b), -2 / (f - n) );
		const Vector3 trans( -(r + l) / (r - l), -(t + b) / (t - b), -(f + n) / (f - n) );

		value *= Matrix4x4(
			scale.x, 0, 0, trans.x,
			0, scale.y, 0, trans.y,
			0, 0, scale.z, trans.z,
			0, 0, 0, 1
		);

		const Vector3 invScale( 1 / scale.x, 1 / scale.y, 1 / scale.z );
		inverse = Matrix4x4(
			invScale.x, 0, 0, -trans.x * invScale.x,
			0, invScale.y, 0, -trans.y * invScale.y,
			0, 0, invScale.z, -trans.z * invScale.z,
			0, 0, 0, 1
		) * inverse;
	}

	void Matrix::Push()
	{
		stack.emplace( value, inverse );
	}

	void Matrix::Pop()
	{
		assert( stack.size() > 0 );

		const auto popped = stack.top();
		value = popped.first;
		inverse = popped.second;
		stack.pop();
	}
}