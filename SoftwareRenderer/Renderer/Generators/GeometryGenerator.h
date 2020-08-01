#pragma once
#include "Renderer/IRenderer.h"
#include "Types.h"
#include "Util/Dictionary.hpp"

namespace Renderer
{
	class GeometryGenerator final
	{
	public:
		GeometryGenerator();
		~GeometryGenerator();

		void Begin( IRenderer::DrawMode mode );
		IGeometryList Generate( const VertexBuffer& vertices );

	private:
		using GeneratorFunction = std::function<void( const std::vector<Vertex>&, IGeometryList& )>;
		static const Dictionary<IRenderer::DrawMode, const GeneratorFunction> table;

		GeneratorFunction generator;
	};

}