#pragma once
#include "IRenderer.h"
#include "Vertex.h"
#include "Math/Matrix4x4.h"

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

		void Begin( DrawMode mode ) override;
		void End() override;
		void AddVertex( float x, float y, float z ) override;

		void LoadIdentity() override;
		void Translate( float x, float y, float z ) override;
		void Rotate( Degree angle, float x, float y, float z ) override;
		void Scale( float x, float y, float z ) override;

	private:
		const HWND hWnd;
		const int width;
		const int height;

		std::unique_ptr<FrameBuffer> backBuffer;
		std::vector<std::unique_ptr<IPrimitive>> primitives;
		std::vector<Vertex> vertices;

		Matrix4x4 transform;
		Matrix4x4 view;

		const std::unique_ptr<PrimitiveGeneratorFactory> factory;
	};

}