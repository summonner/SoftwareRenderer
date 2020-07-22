#pragma once
#include "Renderer/IRenderer.h"
#include "Types.h"

namespace Renderer
{
	class RasterizerGenerator final
	{
	public:
		RasterizerGenerator();
		~RasterizerGenerator();

		void Begin( IRenderer::DrawMode mode, int startIndex );
		void End( int endIndex );
		void Generate( const VertexBuffer& vertices, IRasterizerList& primitives );

	private:
		using GeneratorFunction = std::function<void( const std::vector<Vertex>&, int, int, IRasterizerList& )>;
		static std::map<IRenderer::DrawMode, const GeneratorFunction> table;
		static const GeneratorFunction FindGenerator( IRenderer::DrawMode mode );

		struct Generator
		{
			GeneratorFunction generator;
			int start = 0;
			int end = 0;

			void Generate( const VertexBuffer& vertices, IRasterizerList& primitives );
		};

		Generator temp;
		std::queue<Generator> generators;
	};

}