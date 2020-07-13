#pragma once
#include "IPrimitiveGenerator.h"

namespace Renderer 
{
	class PointGenerator final : public IPrimitiveGenerator
	{
	public:
		PointGenerator();
		~PointGenerator();

		IPrimitiveList Generate( VertexBuffer vertices ) const override;

		static IPrimitiveList Default( VertexBuffer vertices );
	};
}