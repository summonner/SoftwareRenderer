#pragma once
#include "Renderer/IComponent.h"
#include "Math/Vector4.hpp"
#include "Material.h"
#include "ColorMaterial.h"

namespace Renderer
{
	class Light;
	class Material;
	class Vertex;
	class LightingComponent final : public BaseComponent
	{
	public:
		LightingComponent();
		~LightingComponent();

		void Reset() override;
		void SetGlobalAmbient( const Vector4& ambient );

		void Add( std::shared_ptr<const Light> light );
		void Remove( std::shared_ptr<const Light> light );

		Vector4 GetColor( const Vertex& vertex ) const;

	private:
		Vector3 GetView( const Vector3& position ) const;
		Vector4 GetColor( const Vector4& position, const Vector3& normal, const Material& front ) const;

	private:
		std::vector<std::shared_ptr<const Light>> lights;

		Vector4 ambient;
		bool localViewer;
		bool singleColor;
		bool twoSide;

	public:
		Material front;
		Material back;
		ColorMaterial colorMaterial;

	private:
		static Vector4 GetColor( const Light& light, const Material& material, const Vector4& position, const Vector3& normal, const Vector3& view );
	};
}