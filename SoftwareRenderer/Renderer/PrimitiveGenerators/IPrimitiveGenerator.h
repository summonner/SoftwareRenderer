#pragma once

namespace Renderer
{
	class Vertex;
	class IPrimitive;
	using IPrimitiveList = std::vector<std::unique_ptr<IPrimitive>>;
	using VertexBuffer = const std::vector<Vertex>&;

	class IPrimitiveGenerator abstract
	{
	public:
		virtual ~IPrimitiveGenerator() {}

		virtual IPrimitiveList Generate( VertexBuffer vertices ) const abstract;
	};
}