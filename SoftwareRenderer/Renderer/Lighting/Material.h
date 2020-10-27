#pragma once
#include "Math/Vector4.hpp"

namespace Renderer
{
	class Material final
	{
	public:
		Material();
		~Material();

		void Reset();
		void SetShininess( float shininess );
		float GetShininess() const;

	public:
		Vector4 ambient;
		Vector4 diffuse;
		Vector4 specular;
		Vector4 emissive;
		float shininess;
	};
}