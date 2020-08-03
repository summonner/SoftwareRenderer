#include "framework.h"
#include "BlendFunc.h"
#include "Math/Vector4.hpp"

namespace Renderer
{
	BlendFunc::BlendFunc( const Type type )
		: current( table[type] )
	{
	}

	BlendFunc::~BlendFunc()
	{
	}

	void BlendFunc::operator =( const Type type )
	{
		current = table[type];
	}

	Vector4 BlendFunc::operator ()( const Vector4& src, const Vector4& dst ) const
	{
		return current( src, dst );
	}

	const Dictionary<BlendFunc::Type, BlendFunc::Func> BlendFunc::table
	{
		{ Type::Zero, Zero },
		{ Type::One, One },
		{ Type::SrcColor, SrcColor },
		{ Type::OneMinusSrcColor, OneMinusSrcColor },
		{ Type::DstColor, DstColor },
		{ Type::OneMinusDstColor, OneMinusDstColor },
		{ Type::SrcAlpha, SrcAlpha },
		{ Type::OneMinusSrcAlpha, OneMinusSrcAlpha },
		{ Type::DstAlpha, DstAlpha },
		{ Type::OneMinusDstAlpha, OneMinusDstAlpha },
		{ Type::ConstantColor, ConstantColor },
		{ Type::OneMinusConstantColor, OneMinusConstantColor },
		{ Type::ConstantAlpha, ConstantAlpha },
		{ Type::OneMinusConstantAlpha, OneMinusConstantAlpha },
		{ Type::SrcAlphaSaturate, SrcAlphaSaturate },
	};

	Vector4 BlendFunc::constant = Vector4::zero;

	Vector4 BlendFunc::Zero( const Vector4& src, const Vector4& dst )
	{
		return Vector4::zero;
	}

	Vector4 BlendFunc::One( const Vector4& src, const Vector4& dst )
	{
		return Vector4::one;
	}

	Vector4 BlendFunc::SrcColor( const Vector4& src, const Vector4& dst )
	{
		return src;
	}

	Vector4 BlendFunc::OneMinusSrcColor( const Vector4& src, const Vector4& dst )
	{
		return Vector4::one - src;
	}

	Vector4 BlendFunc::DstColor( const Vector4& src, const Vector4& dst )
	{
		return dst;
	}

	Vector4 BlendFunc::OneMinusDstColor( const Vector4& src, const Vector4& dst )
	{
		return Vector4::one - dst;
	}

	Vector4 BlendFunc::SrcAlpha( const Vector4& src, const Vector4& dst )
	{
		return Vector4::one * src.w;
	}
	
	Vector4 BlendFunc::OneMinusSrcAlpha( const Vector4& src, const Vector4& dst )
	{
		return Vector4::one * (1 - src.w);
	}

	Vector4 BlendFunc::DstAlpha( const Vector4& src, const Vector4& dst )
	{
		return Vector4::one * dst.w;
	}

	Vector4 BlendFunc::OneMinusDstAlpha( const Vector4& src, const Vector4& dst )
	{
		return Vector4::one * (1 - dst.w);
	}

	Vector4 BlendFunc::ConstantColor( const Vector4& src, const Vector4& dst )
	{
		return constant;
	}

	Vector4 BlendFunc::OneMinusConstantColor( const Vector4& src, const Vector4& dst )
	{
		return Vector4::one - constant;
	}

	Vector4 BlendFunc::ConstantAlpha( const Vector4& src, const Vector4& dst )
	{
		return Vector4::one * constant.w;
	}

	Vector4 BlendFunc::OneMinusConstantAlpha( const Vector4& src, const Vector4& dst )
	{
		return Vector4::one * (1 - constant.w);
	}

	Vector4 BlendFunc::SrcAlphaSaturate( const Vector4& src, const Vector4& dst )
	{
		return Vector4::one * std::min( src.w, 1 - dst.w );
	}
}