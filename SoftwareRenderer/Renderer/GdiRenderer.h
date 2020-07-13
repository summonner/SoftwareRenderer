#pragma once
#include "IRenderer.h"
#include "Vertex.h"

namespace Renderer
{
	class FrameBuffer;
	class IPrimitive;
	class PrimitiveGeneratorFactory;

	class GdiRenderer final : public IRenderer
	{
	private:
		GdiRenderer( const HWND hWnd, const int width, const int height );
		GdiRenderer( const GdiRenderer& source ) = delete;
	public:
		static GdiRenderer* Create( const HWND hWnd );
		~GdiRenderer() override;

		void Clear() override;
		void Present() override;
		void Present( const HDC dc );

		void Begin( DrawMode mode );
		void End();
		void AddVertex( float x, float y, float z );

	private:
		const HWND hWnd;
		const int width;
		const int height;

		std::unique_ptr<FrameBuffer> backBuffer;
		std::vector<std::unique_ptr<IPrimitive>> primitives;
		std::vector<Vertex> vertices;

		const std::unique_ptr<PrimitiveGeneratorFactory> factory;
	};

}