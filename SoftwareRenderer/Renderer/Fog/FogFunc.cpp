#include "framework.h"
#include "FogFunc.h"

namespace Renderer
{
	namespace FogFunc
	{
		Linear::Linear()
			: start( 0.f )
			, end ( 1.f )
		{
		}

		Linear::~Linear()
		{
		}

		float Linear::operator ()( float c ) const
		{
			return (end - c) / (end - start);
		}

		
		Exp::Exp( int exponent )
			: exponent( exponent )
			, density( 1.f )
		{
		}

		Exp::~Exp()
		{
		}

		float Exp::operator ()( float c ) const
		{
			return ::exp( -1 * Pow( density * c ) );
		}

		float Exp::Pow( float c ) const
		{
			auto p = 1.f;
			for ( auto i = 0; i < exponent; ++i )
			{
				p *= c;
			}
			return p;
		}
	}
}