#pragma once
#include "Renderer/IComponent.h"
#include "StencilFunc.h"
#include "StencilOp.h"

namespace Renderer
{
	class IStencilBufferController abstract : public BaseComponent
	{
	public:
		virtual ~IStencilBufferController() {};

		virtual void Clear() abstract;
		virtual void SetClearValue( StencilValue value ) abstract;


	public:
		class Properties
		{
		public:
			StencilFunc func;
			StencilOp pass;
			StencilOp depthFail;
			StencilOp fail;
			StencilValue ref = 0;
			StencilValue mask = std::numeric_limits<StencilValue>::max();

			inline bool Test( StencilValue current ) const
			{
				return func( ref, current );
			}

			inline StencilValue Write( StencilOp op, StencilValue current ) const
			{
				return op( current, ref ) & mask;
			}
		};

		Properties front;
		Properties back;
	};
}