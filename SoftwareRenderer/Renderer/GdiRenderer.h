#pragma once
#include "IRenderer.h"
#include "Vertex.h"
#include "Math/Matrix4x4.h"
#include "Math/Bounds.h"
#include "Generators/GeometryGenerator.h"

namespace Renderer
{
	class FrameBuffer;
	class DepthBuffer;
	class IRasterizer;
	class IGeometry;
	class ITexture;

	class GdiRenderer final : public IRenderer
	{
	public:
		static std::unique_ptr<GdiRenderer> Create( const HWND hWnd );
		GdiRenderer( const HWND hWnd, const int width, const int height );
		GdiRenderer( const GdiRenderer& source ) = delete;
		~GdiRenderer() override;

		void Clear() override;
		void SetClearColor( float r, float g, float b, float a ) override;
		void Present() override;
		void Present( const HDC dc );

		void Draw( const Renderer::Mesh& renderer ) override;

		void Reset() override;

	private:
		Vertex TransformVertex( Vertex v ) const;
		void Render();

	private:
		const HWND hWnd;
		const Bounds bounds;

		std::unique_ptr<FrameBuffer> backBuffer;

		GeometryGenerator generator;

		Vertex temp;
		std::vector<Vertex> vertices;
	};

}