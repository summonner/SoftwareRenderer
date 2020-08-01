#pragma once

namespace Renderer
{
	class IGeometry;
	class Vertex;

	using IGeometryList = std::vector<std::unique_ptr<IGeometry>>;
	using VertexBuffer = const std::vector<Vertex>&;
}