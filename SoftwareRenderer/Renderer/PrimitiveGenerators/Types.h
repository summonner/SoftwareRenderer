#pragma once

namespace Renderer
{
	class IPrimitive;
	class Vertex;

	using IPrimitiveList = std::vector<std::unique_ptr<IPrimitive>>;
	using VertexBuffer = const std::vector<Vertex>&;
}