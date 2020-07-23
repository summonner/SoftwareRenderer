#pragma once
#include "IRenderer.h"
#include "Vertex.h"
#include "Math/Matrix4x4.h"
#include "Math/Bounds.h"

class Bitmap;
namespace Renderer
{
	class FrameBuffer;
	class DepthBuffer;
	class IRasterizer;
	class RasterizerGenerator;

	class GdiRenderer final : public IRenderer
	{
	public:
		GdiRenderer( const HWND hWnd, const int width, const int height );
		GdiRenderer( const GdiRenderer& source ) = delete;
		~GdiRenderer() override;

		void Clear() override;
		void Present() override;
		void Present( const HDC dc );

		void Begin( DrawMode mode ) override;
		void End() override;
		void Color( float r, float g, float b ) override;
		void AddVertex( float x, float y, float z ) override;

		void LoadIdentity() override;
		void Translate( float x, float y, float z ) override;
		void Rotate( Degree angle, float x, float y, float z ) override;
		void Scale( float x, float y, float z ) override;

		void Viewport( float left, float bottom, float width, float height ) override;
		void Frustum( float left, float right, float top, float bottom, float near, float far ) override;
		void Perspective( Degree fovY, float aspect, float near, float far ) override;
		void Ortho( float left, float right, float top, float bottom, float near, float far ) override;

		void BindTexture( std::shared_ptr<const Bitmap> bitmap ) override;
		void TexCoord( float u, float v ) override;

	private:
		const HWND hWnd;
		const Bounds bounds;

		std::unique_ptr<FrameBuffer> backBuffer;
		std::unique_ptr<DepthBuffer> depthBuffer;
		std::vector<std::unique_ptr<IRasterizer>> rasterizers;
		std::vector<Vertex> vertices;

		Vertex temp;
		Matrix4x4 transform;
		Matrix4x4 projection;
		Matrix4x4 viewport;

		const std::unique_ptr<RasterizerGenerator> generator;

		std::shared_ptr<const Bitmap> bitmap;
	};

}