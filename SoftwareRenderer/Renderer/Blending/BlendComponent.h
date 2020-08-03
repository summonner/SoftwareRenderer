#pragma once
#include "BlendFunc.h"

namespace Renderer
{
	class BlendComponent final
	{
	public:
		BlendComponent();
		~BlendComponent();

		void SetEnable( bool enable );
		bool IsEnable() const;

		Vector4 operator ()( const Vector4& srcColor, const Vector4& dstColor ) const;
		void SetBlendFunc( const BlendFunc::Type src, const BlendFunc::Type dst );
		void SetBlendColor( const Vector4& color );

	private:
		bool enabled;
		BlendFunc srcFunc;
		BlendFunc dstFunc;
	};

}