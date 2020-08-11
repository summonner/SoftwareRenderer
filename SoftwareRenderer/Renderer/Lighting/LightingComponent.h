#pragma once
#include "Renderer/IComponent.h"
#include "Math/Vector4.hpp"
#include "Material.h"

namespace Renderer
{
	class Light;
	class Material;
	class LightingComponent final : public BaseComponent
	{
	public:
		LightingComponent();
		~LightingComponent();

		void Reset() override;
		void SetGlobalAmbient( const Vector4& ambient );

		void Add( std::shared_ptr<const Light> light );
		void Remove( std::shared_ptr<const Light> light );

		Vector4 GetColor( const Vector4& position, const Vector3& normal ) const;

	private:
		Vector3 GetView( const Vector3& position ) const;

	private:
		std::vector<std::shared_ptr<const Light>> lights;

		Vector4 ambient;
		bool localViewer;
		bool singleColor;
		bool twoSide;

	public:
		Material front;
		Material back;

	private:
		static Vector4 GetColor( const Light& light, const Material& material, const Vector4& position, const Vector3& normal, const Vector3& view );
	};
}