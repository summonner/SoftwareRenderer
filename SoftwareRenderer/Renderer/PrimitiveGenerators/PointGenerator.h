#pragma once
#include "IPrimitiveGenerator.h"

namespace Renderer 
{
	class PointGenerator final : public IPrimitiveGenerator
	{
	public:
		PointGenerator();
		~PointGenerator();

		void AddVertex( const Vector4& vertex );
		IPrimitiveList Flush();

	private:
		IPrimitiveList primitives;
	};
}