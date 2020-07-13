#pragma once
#include "Math/Vector.h"

namespace Renderer
{
	class IPrimitive;
	using IPrimitiveList = std::vector<std::unique_ptr<IPrimitive>>;

	class IPrimitiveGenerator abstract
	{
	public:
		virtual ~IPrimitiveGenerator() {}

		virtual void AddVertex( const Vector4& vertex ) abstract;
		virtual IPrimitiveList Flush() abstract;
	};
}