#pragma once
#include "Renderer/IRenderer.h"
#include "Types.h"

namespace Renderer
{
	class PrimitiveGenerator final
	{
	public:
		PrimitiveGenerator();
		~PrimitiveGenerator();

		void Begin( IRenderer::DrawMode mode, int startIndex );
		void End( int endIndex );
		void Generate( const VertexBuffer& vertices, IPrimitiveList& primitives );

	private:
		using GeneratorFunction = std::function<void( const std::vector<Vertex>&, int, int, IPrimitiveList& )>;
		static std::map<IRenderer::DrawMode, const GeneratorFunction> table;
		static const GeneratorFunction FindGenerator( IRenderer::DrawMode mode );

		struct Generator
		{
			GeneratorFunction generator;
			int start;
			int end;

			void Generate( const VertexBuffer& vertices, IPrimitiveList& primitives );
		};

		Generator temp;
		std::queue<Generator> generators;
	};

}