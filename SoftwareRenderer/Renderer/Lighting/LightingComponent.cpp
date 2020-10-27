#include "framework.h"
#include "LightingComponent.h"
#include "Light.h"
#include "Renderer/Vertex.h"

namespace Renderer
{

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

		front = Material();
		back = Material();
	}

	void LightingComponent::SetGlobalAmbient( const Vector4& ambient )
	{
		this->ambient = ambient;
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

	Vector4 LightingComponent::GetColor( const Vertex& vertex ) const
	{
		if ( enabled == false )
		{
			return vertex.color;
		}

		if ( vertex.normal == Vector3::zero )
		{
			return vertex.color;
		}

		const auto material = colorMaterial.GetFront( front, vertex.color );
		return GetColor( vertex.position, vertex.normal, material );
	}

	Vector4 LightingComponent::GetColor( const Vector4& position, const Vector3& normal, const Material& material ) const
	{
		const auto view = GetView( position );
		Vector4 result = material.emissive;
		result += material.ambient * ambient;
		for ( const auto& light : lights )
		{
			result += GetColor( *light, material, position, normal, view );
		}

		return Clamp( result );
	}

	Vector4 LightingComponent::GetColor( const Light& light, const Material& material, const Vector4& v, const Vector3& normal, const Vector3& view )
	{
		const Vector3 l = Vector3( light - v ).Normalize();
		const Vector3 h = (l + view).Normalize();
		const auto attenuation = light.Attenuation( v );
		const auto spot = light.Spot( v );
		const auto LN = Light::Dot( normal, l );

		Vector4 result( 0, 0, 0, 1 );
		result += material.ambient * light.ambient;
		result += material.diffuse * light.diffuse * LN;
		if ( LN != 0 )
		{
			result += material.specular * light.specular * pow( Light::Dot( normal, h ), material.shininess );
		}
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