#pragma once

namespace Renderer
{
	class BlendFunc final
	{
	public:
		enum class Type
		{
			Zero,
			One,
			SrcColor,
			OneMinusSrcColor,
			DstColor,
			OneMinusDstColor,
			SrcAlpha,
			OneMinusSrcAlpha,
			DstAlpha,
			OneMinusDstAlpha,
			ConstantColor,
			OneMinusConstantColor,
			ConstantAlpha,
			OneMinusConstantAlpha,
			SrcAlphaSaturate,
		};

	public:
		BlendFunc( const Type type );
		~BlendFunc();

		void operator =( const Type type );
		Vector4 operator ()( const Vector4& src, const Vector4& dst ) const;

		static Vector4 constant;

	private:
		using Func = std::function<Vector4( const Vector4&, const Vector4& )>;
		Func current;
		static const Dictionary<Type, Func> table;

		static Vector4 Zero( const Vector4& src, const Vector4& dst );
		static Vector4 One( const Vector4& src, const Vector4& dst );
		static Vector4 SrcColor( const Vector4& src, const Vector4& dst );
		static Vector4 OneMinusSrcColor( const Vector4& src, const Vector4& dst );
		static Vector4 DstColor( const Vector4& src, const Vector4& dst );
		static Vector4 OneMinusDstColor( const Vector4& src, const Vector4& dst );
		static Vector4 SrcAlpha( const Vector4& src, const Vector4& dst );
		static Vector4 OneMinusSrcAlpha( const Vector4& src, const Vector4& dst );
		static Vector4 DstAlpha( const Vector4& src, const Vector4& dst );
		static Vector4 OneMinusDstAlpha( const Vector4& src, const Vector4& dst );
		static Vector4 ConstantColor( const Vector4& src, const Vector4& dst );
		static Vector4 OneMinusConstantColor( const Vector4& src, const Vector4& dst );
		static Vector4 ConstantAlpha( const Vector4& src, const Vector4& dst );
		static Vector4 OneMinusConstantAlpha( const Vector4& src, const Vector4& dst );
		static Vector4 SrcAlphaSaturate( const Vector4& src, const Vector4& dst );
	};
}

using BlendFunc = Renderer::BlendFunc::Type;