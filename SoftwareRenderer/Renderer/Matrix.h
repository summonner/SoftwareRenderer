#pragma once
#include "Math/Matrix4x4.h"

#undef near
#undef far

namespace Renderer
{
	class Matrix final
	{
	public:
		Matrix();
		~Matrix();

		void Reset();
		void Translate( float x, float y, float z );
		void Translate( const Vector3& value );
		void Rotate( Degree angle, float x, float y, float z );
		void Scale( float x, float y, float z );
		void LookAt( const Vector3& eye, const Vector3& center, const Vector3& up );

		void Frustum( float left, float right, float top, float bottom, float near, float far );
		void Perspective( Degree fovY, float aspect, float near, float far );
		void Ortho( float left, float right, float bottom, float top, float near, float far );

		inline operator Matrix4x4() const
		{
			return value;
		}

		inline Matrix4x4 Inverse() const
		{
			assert( inverse( 1, 1 ) != INFINITY );
			return inverse;
		}

		inline Vector4 operator *( const Vector4& vector ) const
		{
			return value * vector;
		}

		Matrix Mult( const float m[16] );

		void Push();
		void Pop();

	private:
		Matrix4x4 value;
		Matrix4x4 inverse;
		std::stack<std::pair<Matrix4x4, Matrix4x4>> stack;
	};
}