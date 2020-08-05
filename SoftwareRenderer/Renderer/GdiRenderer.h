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

		void Begin( DrawMode mode ) override;
		void End() override;
		void Color( float r, float g, float b, float a ) override;
		void TexCoord( float u, float v ) override;
		void Normal( float x, float y, float z ) override;
		void AddVertex( float x, float y, float z ) override;

		void LoadIdentity() override;
		void Translate( float x, float y, float z ) override;
		void Rotate( Degree angle, float x, float y, float z ) override;
		void Scale( float x, float y, float z ) override;

		void Viewport( int left, int bottom, int width, int height ) override;
		void Frustum( float left, float right, float top, float bottom, float near, float far ) override;
		void Perspective( Degree fovY, float aspect, float near, float far ) override;
		void Ortho( float left, float right, float top, float bottom, float near, float far ) override;

	private:

	private:
		const HWND hWnd;
		const Bounds bounds;

		std::unique_ptr<FrameBuffer> backBuffer;

		GeometryGenerator generator;

		Vertex temp;
		std::vector<Vertex> vertices;

		Matrix4x4 transform;
		Matrix4x4 invTransform;
		Matrix4x4 projection;
		Matrix4x4 viewport;
	};

}