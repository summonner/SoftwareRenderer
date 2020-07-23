#include "framework.h"
#include "GdiRenderer.h"
#include "FrameBuffer.h"
#include "DepthBuffer.h"
#include "Rasterizer/IRasterizer.h"
#include "Rasterizer/RasterizedPixel.h"
#include "RasterizerGenerators/RasterizerGenerator.h"
#include "Math/Vector3.hpp"
#include "Texturing/ITexture.h"

namespace Renderer
{
	GdiRenderer::GdiRenderer( const HWND hWnd, const int width, const int height )
		: hWnd( hWnd )
		, bounds( width, height )
		, generator( std::make_unique<RasterizerGenerator>() )
		, depthBuffer( std::make_unique<DepthBuffer>( width, height ) )
	{
		auto dc = GetDC( hWnd );
		backBuffer = std::make_unique<FrameBuffer>( dc, width, height );
		ReleaseDC( hWnd, dc );
	}
	
	GdiRenderer::~GdiRenderer()
	{
	}

	void GdiRenderer::Clear()
	{
		backBuffer->Clear();
		depthBuffer->Clear();
	}

	void GdiRenderer::Present()
	{
		InvalidateRect( hWnd, nullptr, false );
	}

	void GdiRenderer::Present( const HDC dc )
	{
		backBuffer->BitBlt( dc );
	}

	void GdiRenderer::Begin( DrawMode mode )
	{
		generator->Begin( mode );
	}

	void GdiRenderer::End()
	{
		for ( auto& vertex : vertices )
		{
			vertex.Process( projection, viewport );
		}

		auto& rasterizers = generator->Generate( vertices );

		for ( const auto& rasterizer : rasterizers )
		{
			rasterizer->Rasterize( bounds, [this]( const RasterizedPixel& p )
			{
				if ( depthBuffer->Test( p.coordinate, p.depth ) == false )
				{
					return;
				}

				Vector4 color = p.color;
				if ( texture != nullptr )
				{
					color *= texture->GetPixel( p.texcoord );
				}

				backBuffer->SetPixel( p.coordinate, color );
			} );
		}

		vertices.clear();
		generator->Flush();
	}

	void GdiRenderer::Color( float r, float g, float b )
	{
		temp.color = Vector4( r, g, b, 1 );
	}

	void GdiRenderer::AddVertex( float x, float y, float z )
	{
		Vector4 v( x, y, z, 1.f );
		auto t = transform * v;

		temp.position = t;
		vertices.push_back( temp );
	}

	void GdiRenderer::LoadIdentity()
	{
		transform = Matrix4x4::identity;
	}

	void GdiRenderer::Translate( float x, float y, float z )
	{
		transform = transform * Matrix4x4::Translate( Vector3( x, y, z ) );
	}

	void GdiRenderer::Rotate( Degree angle, float x, float y, float z )
	{
		transform = transform * Matrix4x4::Rotate( angle * PI / 180, Vector3( x, y, z ) );
	}

	void GdiRenderer::Scale( float x, float y, float z )
	{
		transform = transform * Matrix4x4::Scale( Vector3( x, y, z ) );
	}

	void GdiRenderer::Viewport( float left, float bottom, float width, float height )
	{
		auto halfWidth = width * 0.5f;
		auto halfHeight = height * 0.5f;
		viewport = Matrix4x4(
			halfWidth, 0, 0, halfWidth + left,
			0, halfHeight, 0, halfHeight + bottom,
			0, 0, 0, 1,
			0, 0, 0, 1
		);
	}

	void GdiRenderer::Frustum( float l, float r, float t, float b, float n, float f )
	{
		projection = Matrix4x4(
			2 * n / (r - l), 0, (r + l) / (r - l), 0,
			0, 2 * n / (t - b), (t + b) / (t - b), 0,
			0, 0, -(f + n) / (f - n), -2 * f * n / (f - n),
			0, 0, -1, 0
		);
	}

	void GdiRenderer::Perspective( Degree fovY, float aspect, float near, float far )
	{
		auto halfHeight = near * tanf( fovY * PI / 180 / 2 );
		auto halfWidth = halfHeight * aspect;
		projection = Matrix4x4(
			near / halfWidth, 0, 0, 0,
			0, near / halfHeight, 0, 0,
			0, 0, -(far + near) / (far - near), -2 * far * near / (far - near),
			0, 0, -1, 0
		);
	}

	void GdiRenderer::Ortho( float l, float r, float t, float b, float n, float f )
	{
		projection = Matrix4x4(
			2 / (r - l), 0, 0, -(r + l) / (r - l),
			0, 2 / (t - b), 0, -(t + b) / (t - b),
			0, 0, 2 / (f - n), -(f + n) / (f - n),
			0, 0, 0, 1
		);
	}

	void GdiRenderer::BindTexture( std::shared_ptr<const ITexture> texture )
	{
		this->texture = texture;
	}

	void GdiRenderer::TexCoord( float u, float v )
	{
		temp.texcoord = Vector2( u, v );
	}
}