#pragma once
#include "DepthFunc.h"
#include "Renderer/IComponent.h"

namespace Renderer
{
	class IDepthBufferController abstract : public BaseComponent
	{
	public:
		virtual ~IDepthBufferController() {}

		virtual void Clear() abstract;
		virtual void SetClearValue( const float value ) abstract;
		virtual void SetDepthFunc( const DepthFunc::Type type ) abstract;
		virtual void SetWrite( bool enable ) abstract;
		virtual float Get( const Vector2Int& coordinate ) const abstract;
	};
}