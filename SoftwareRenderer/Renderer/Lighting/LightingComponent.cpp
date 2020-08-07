#include "framework.h"
#include "LightingComponent.h"
#include "Light.h"
#include "Material.h"

namespace Renderer
{
	Material material;

	LightingComponent::LightingComponent()
		: ambient( 0.2f, 0.2f, 0.2f, 1.0f )
		, localViewer( false )
		, singleColor( true )
		, twoSide( false )
	{
	}

	LightingComponent::~LightingComponent()
	{
	}

	void LightingComponent::Reset()
	{
		BaseComponent::Reset();
		lights.clear();

		ambient = Vector4( 0.2f, 0.2f, 0.2f, 1.0f );
		localViewer = false;
		singleColor = true;
		twoSide = false;
	}

	void LightingComponent::Add( std::shared_ptr<const Light> light )
	{
		if ( const auto found = std::find( lights.begin(), lights.end(), light ); found != lights.end() )
		{
			return;
		}

		lights.push_back( light );
	}

	void LightingComponent::Remove( std::shared_ptr<const Light> light )
	{
		if ( const auto found = std::find( lights.begin(), lights.end(), light ); found != lights.end() )
		{
			lights.erase( found );
		}
	}

	Vector4 LightingComponent::GetColor( const Vector4& v, const Vector3& normal ) const
	{
		if ( enabled == false )
		{
			return Vector4::one;
		}

		const auto view = GetView( v );
		Vector4 result = material.emmisive;
		result += material.ambient * ambient;
		for ( const auto& light : lights )
		{
			result += GetColor( *light, material, v, normal, view );
		}

		return result;
	}

	Vector4 LightingComponent::GetColor( const Light& light, const Material& material, const Vector4& v, const Vector3& normal, const Vector3& view )
	{
		const Vector3 l = Vector3( light - v ).Normalize();
		const Vector3 h = (l + view).Normalize();
		const auto attenuation = light.Attenuation( v );
		const auto spot = light.Spot( v );

		Vector4 result( 0, 0, 0, 1 );
		result += material.ambient * light.ambient;
		result += material.diffuse * light.diffuse * Light::Dot( normal, l );
		result += material.specular * light.specular * pow( Light::Dot( normal, h ), material.shiness );
		return result * attenuation * spot;
	}

	Vector3 LightingComponent::GetView( const Vector3& v ) const
	{
		if ( localViewer == true )
		{
			return (-v).Normalize();
		}
		else
		{
			return Vector3::front;
		}
	}
}