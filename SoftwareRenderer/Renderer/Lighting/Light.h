#pragma once
#include "Math/Vector4.hpp"
#include "Math/Vector3.hpp"

namespace Renderer
{
	class Light final
	{
	public:
		Light();
		~Light();

		Vector4 operator -( const Vector4& p ) const;
		static friend Vector4 operator -( const Vector4& p, const Light& light );

		float Attenuation( const Vector4& p ) const;
		float Spot( const Vector4& p ) const;

		static float Dot( const Vector3& left, const Vector3& right );

	public:
		Vector4 ambient;
		Vector4 diffuse;
		Vector4 specular;
		
		Vector4 position;
		Vector3 direction;
		float exponent;
		float cosCutoff;
		Vector3 attenuation;
	};

	Vector4 operator -( const Vector4& p, const Light& light )
	{
		if ( light.position.w == 0 )
		{
			return -light.position;
		}
		else
		{
			return p - light.position;
		}
	}
}