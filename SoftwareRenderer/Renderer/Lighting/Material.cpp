#include "framework.h"
#include "Material.h"

namespace Renderer
{
	Material::Material()
		: ambient( 0.2f, 0.2f, 0.2f, 1.0f )
		, diffuse( 0.8f, 0.8f, 0.8f, 1.0f )
		, specular( 0.0f, 0.0f, 0.0f, 1.0f )
		, emmisive( 0.0f, 0.0f, 0.0f, 1.0f )
		, shiness( 0.0f )
	{
	}


	Material::~Material()
	{
	}
}