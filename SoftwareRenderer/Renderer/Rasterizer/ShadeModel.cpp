#include "framework.h"
#include "ShadeModel.h"
#include "Math/Vector4.hpp"

namespace Renderer
{
	ShadeModel::Type ShadeModel::type = ShadeModel::Type::Smooth;

	ShadeModel::ShadeFunc ShadeModel::FlatFunc( const Vector4& color )
	{
		if ( IsFlat() == false )
		{
			return nullptr;
		}

		return [color]( float t )
		{
			return color;
		};
	}

	ShadeModel::ShadeFunc ShadeModel::SmoothFunc( const Vector4& a, const Vector4& b )
	{
		assert( type == Type::Smooth );
		return [a, b]( float t ) 
		{ 
			return Vector4::Lerp( a, b, t );
		};
	}

	bool ShadeModel::IsFlat()
	{
		return type == Type::Flat;
	}
}