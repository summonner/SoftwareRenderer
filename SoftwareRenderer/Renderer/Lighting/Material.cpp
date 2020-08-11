#include "framework.h"
#include "Material.h"

namespace Renderer
{
	Material::Material()
		: ambient( 0.2f, 0.2f, 0.2f, 1.0f )
		, diffuse( 0.8f, 0.8f, 0.8f, 1.0f )
		, specular( 0.0f, 0.0f, 0.0f, 1.0f )
		, emissive( 0.0f, 0.0f, 0.0f, 1.0f )
		, shininess( 0.0f )
	{
	}


	Material::~Material()
	{
	}

	void Material::SetShininess( float shininess )
	{
		this->shininess = std::clamp( shininess, 0.f, 128.f );
	}

	float Material::GetShininess() const
	{
		return shininess;
	}
}