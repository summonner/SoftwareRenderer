#pragma once
#include "Renderer/IComponent.h"

namespace Renderer
{
	class Material;
	class ColorMaterial final : public BaseComponent
	{
	public:
		enum class Mode
		{
			AmbientAndDiffuse,
			Ambient,
			Diffuse,
			Specular,
			Emission,
		};

	public:
		ColorMaterial();
		~ColorMaterial();

		Material GetFront( const Material& material, const Vector4& vertexColor ) const;
		Material GetBack( const Material& material, const Vector4& vertexColor ) const;

	private:
		Material Apply( const Material& material, const Vector4& vertexColor, Mode mode ) const;

	public:
		Mode front;
		Mode back;

	private:
		using ApplyFunc = std::function<void( Material& cloned, const Vector4& vertexColor )>;
		static void AmbientAndDiffuse( Material& cloned, const Vector4& vertexColor );
		static void Ambient( Material& cloned, const Vector4& vertexColor );
		static void Diffuse( Material& cloned, const Vector4& vertexColor );
		static void Specular( Material& cloned, const Vector4& vertexColor );
		static void Emission( Material& cloned, const Vector4& vertexColor );
		static const Dictionary<Mode, ApplyFunc> table;
	};
}

using ColorMaterial = Renderer::ColorMaterial::Mode;