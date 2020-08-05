#include "framework.h"
#include "Light.h"

namespace Renderer
{
	Light::Light()
		: ambient( 0, 0, 0, 1 )
		, diffuse( 1, 1, 1, 1 )
		, specular( 1, 1, 1, 1 )
		, position( 0, 0, 1, 0 )
		, direction( 0, 0, -1 )
		, exponent( 0 )
		, cosCutoff( -1 )
		, attenuation( 1, 0, 0 )
	{
	}

	Light::~Light()
	{
	}

	Vector4 Light::operator -( const Vector4& p ) const
	{
		if ( position.w == 0 )
		{
			return position;
		}
		else
		{
			return position - p;
		}
	}

	float Light::Attenuation( const Vector4& p ) const
	{
		if ( position.w == 0 )
		{
			return 1.f;
		}

		const auto l = Vector3(*this - p);
		const auto sqDistance = l.Dot( l );
		const auto v = Vector3( 1, std::sqrt( sqDistance ), sqDistance );
		return attenuation.Dot( v );
	}

	float Light::Spot( const Vector4& p ) const
	{
		if ( cosCutoff < 0 )
		{
			return 1.f;
		}

		const auto dot = Dot( p - (*this), direction );
		if ( dot < cosCutoff )
		{
			return 0.f;
		}

		return pow( dot, exponent );
	}

	float Light::Dot( const Vector3& left, const Vector3& right )
	{
		const auto dot = left.Dot( right );
		return std::max( dot, 0.f );
	}
}