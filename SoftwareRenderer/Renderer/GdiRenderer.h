#pragma once
#include "IRenderer.h"
#include "Vertex.h"
#include "Math/Matrix4x4.h"

namespace Renderer
{
	class FrameBuffer;
	class IPrimitive;
	class PrimitiveGenerator;

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
		void SetColor( float r, float g, float b ) override;
		void AddVertex( float x, float y, float z ) override;

		void LoadIdentity() override;
		void Translate( float x, float y, float z ) override;
		void Rotate( Degree angle, float x, float y, float z ) override;
		void Scale( float x, float y, float z ) override;

		void Viewport( float left, float bottom, float width, float height ) override;
		void Frustum( float left, float right, float top, float bottom, float near, float far ) override;
		void Perspective( float fovY, float aspect, float near, float far ) override;
		void Ortho( float left, float right, float top, float bottom, float near, float far ) override;

	private:
		const HWND hWnd;
		const int width;
		const int height;

		std::unique_ptr<FrameBuffer> backBuffer;
		std::vector<std::unique_ptr<IPrimitive>> primitives;
		std::vector<Vertex> vertices;

		Vertex temp;
		Matrix4x4 transform;
		Matrix4x4 projection;
		Matrix4x4 viewport;

		const std::unique_ptr<PrimitiveGenerator> generator;
	};

}