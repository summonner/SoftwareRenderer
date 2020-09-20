#include "framework.h"
#include "ColorMaterial.h"
#include "Material.h"

namespace Renderer
{
	const Dictionary<ColorMaterial::Mode, ColorMaterial::ApplyFunc> ColorMaterial::table 
	{
		{ Mode::AmbientAndDiffuse, AmbientAndDiffuse },
		{ Mode::Ambient, Ambient },
		{ Mode::Diffuse, Diffuse },
		{ Mode::Specular, Specular },
		{ Mode::Emission, Emission },
	};

	ColorMaterial::ColorMaterial()
		: front( Mode::AmbientAndDiffuse )
		, back( Mode::AmbientAndDiffuse )
	{
	}

	ColorMaterial::~ColorMaterial()
	{
	}

	Material ColorMaterial::GetFront( const Material& material, const Vector4& vertexColor ) const
	{
		return Apply( material, vertexColor, front );
	}

	Material ColorMaterial::GetBack( const Material& material, const Vector4& vertexColor ) const
	{
		return Apply( material, vertexColor, back );
	}

	Material ColorMaterial::Apply( const Material& material, const Vector4& vertexColor, Mode mode ) const
	{
		if ( enabled == false )
		{
			return material;
		}

		auto clone = material;
		table[mode]( clone, vertexColor );
		return clone;
	}

	void ColorMaterial::AmbientAndDiffuse( Material& cloned, const Vector4& vertexColor )
	{
		cloned.ambient = vertexColor;
		cloned.diffuse = vertexColor;
	}

	void ColorMaterial::Ambient( Material& cloned, const Vector4& vertexColor )
	{
		cloned.ambient = vertexColor;
	}

	void ColorMaterial::Diffuse( Material& cloned, const Vector4& vertexColor )
	{
		cloned.diffuse = vertexColor;
	}

	void ColorMaterial::Specular( Material& cloned, const Vector4& vertexColor )
	{
		cloned.specular = vertexColor;
	}

	void ColorMaterial::Emission( Material& cloned, const Vector4& vertexColor )
	{
		cloned.emissive = vertexColor;
	}
}