#pragma once

namespace Renderer
{
	class IRasterizer;
	class Vertex;

	using IRasterizerList = std::vector<std::unique_ptr<IRasterizer>>;
	using VertexBuffer = const std::vector<Vertex>&;
}