#pragma once
#include "BlendFunc.h"
#include "Renderer/IComponent.h"

namespace Renderer
{
	class BlendComponent final : public BaseComponent
	{
	public:
		BlendComponent();
		~BlendComponent();

		void Reset() override;
		std::function<Vector4( const Vector4&, const Vector4& )> AsFunc() const;
		Vector4 Apply( const Vector4& srcColor, const Vector4& dstColor ) const;
		void SetBlendFunc( const BlendFunc::Type src, const BlendFunc::Type dst );
		void SetBlendColor( const Vector4& color );

	private:
		BlendFunc srcFunc;
		BlendFunc dstFunc;
	};

}