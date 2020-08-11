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
		void Rotate( Degree angle, float x, float y, float z );
		void Scale( float x, float y, float z );

		void Viewport( int left, int top, int width, int height );
		void Frustum( float left, float right, float top, float bottom, float near, float far );
		void Perspective( Degree fovY, float aspect, float near, float far );
		void Ortho( float left, float right, float top, float bottom, float near, float far );

		inline operator Matrix4x4() const
		{
			return value;
		}

		inline Matrix4x4 Inverse() const
		{
			return inverse;
		}

		inline Vector4 operator *( const Vector4& vector ) const
		{
			return value * vector;
		}

	private:
		Matrix4x4 value;
		Matrix4x4 inverse;
	};
}