#pragma once
#include "IPrimitiveGenerator.h"

namespace Renderer
{
	class LineGenerator final : public IPrimitiveGenerator
	{
	public:
		LineGenerator();
		~LineGenerator();

		IPrimitiveList Generate( VertexBuffer vertices ) const override;

		static IPrimitiveList Default( VertexBuffer vertices );
		static IPrimitiveList Strip( VertexBuffer vertices );
		static IPrimitiveList Loop( VertexBuffer vertices );
	};
}