#include "framework.h"
#include "GdiRenderer.h"
#include "FrameBuffer.h"
#include "Geometry/IGeometry.h"
#include "Rasterizer/IRasterizer.h"
#include "Rasterizer/RasterizedPixel.h"
#include "Rasterizer/DerivativeTexcoord.h"
#include "Math/Vector3.hpp"
#include "Math/Degree.h"

namespace Renderer
{
	std::unique_ptr<GdiRenderer> GdiRenderer::Create( const HWND hWnd )
	{
		RECT rect;
		GetClientRect( hWnd, &rect );
		return std::make_unique<GdiRenderer>( hWnd, rect.right, rect.bottom );
	}

	GdiRenderer::GdiRenderer( const HWND hWnd, const int width, const int height )
		: IRenderer( width, height )
		, hWnd( hWnd )
		, bounds( width, height )
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
	}

	void GdiRenderer::SetClearColor( float r, float g, float b, float a )
	{
		backBuffer->SetClearValue( Vector4( r, g, b, a ) );
	}

	void GdiRenderer::Present()
	{
		InvalidateRect( hWnd, nullptr, false );
	}

	void GdiRenderer::Present( const HDC dc )
	{
		backBuffer->BitBlt( dc );
	}

	void GdiRenderer::Render()
	{
		for ( auto& vertex : vertices )
		{
			vertex.color *= lighting.GetColor( vertex.position, vertex.normal );
			vertex.Process( projection );
		}

		auto geometries = generator.Generate( vertices );
		for ( const auto& geometry : geometries )
		{
			auto rasterizer = geometry->Clip( viewport );
			if ( rasterizer == nullptr )
			{
				continue;
			}

			if ( cullFace.Apply( *rasterizer ) == false )
			{
				continue;
			}

			const auto derivatives = rasterizer->Derivative( texture.IsEnable() );
			rasterizer->Rasterize( bounds, [&]( const RasterizedPixel& p )
			{
				if ( depthBuffer.Test( p ) == false )
				{
					return;
				}

				Vector4 color = p.GetColor();
				color *= texture.GetColor( p, derivatives );

				backBuffer->SetPixel( p.coordinate, color, blender.AsFunc() );
			} );
		}

		vertices.clear();
	}

	void GdiRenderer::Draw( const Mesh& mesh )
	{
		generator.Begin( mesh.drawMode );
		vertices.reserve( mesh.size() );
		std::transform( mesh.begin(), mesh.end(), std::back_inserter( vertices ),
			[this]( const Vertex& v ) { return TransformVertex( v ); } );
//			std::bind( &GdiRenderer::TransformVertex, *this, std::placeholders::_1 ) );
		Render();
	}

	Vertex GdiRenderer::TransformVertex( Vertex v ) const
	{
		v.position = transform * v.position;
		v.normal = Vector4( v.normal, 0 ) * invTransform;
		return v;
	}

	void GdiRenderer::LoadIdentity()
	{
		transform = Matrix4x4::identity;
		invTransform = Matrix4x4::identity;
	}

	void GdiRenderer::Translate( float x, float y, float z )
	{
		transform = transform * Matrix4x4::Translate( Vector3( x, y, z ) );
		invTransform = Matrix4x4::Translate( Vector3( x, y, z ) * -1 ) * invTransform;
	}

	void GdiRenderer::Rotate( Degree angle, float x, float y, float z )
	{
		const auto rotate = Matrix4x4::Rotate( angle, Vector3( x, y, z ) );
		transform = transform * rotate;
		invTransform = rotate.Transpose() * invTransform;
	}

	void GdiRenderer::Scale( float x, float y, float z )
	{
		transform = transform * Matrix4x4::Scale( Vector3( x, y, z ) );
		invTransform = Matrix4x4::Scale( Vector3( 1 / x, 1 / y, 1 / z ) ) * invTransform;
	}

	void GdiRenderer::Viewport( int left, int bottom, int width, int height )
	{
		auto halfWidth = width * 0.5f;
		auto halfHeight = height * 0.5f;
		viewport = Matrix4x4(
			halfWidth, 0, 0, halfWidth + left + 0.5f,
			0, halfHeight, 0, halfHeight + bottom + 0.5f,
			0, 0, 1.0f, 0,
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

	void GdiRenderer::Reset()
	{
		IRenderer::Reset();

		transform = Matrix4x4::identity;
		invTransform = Matrix4x4::identity;
		projection = Matrix4x4::identity;
		viewport = Matrix4x4::identity;

		vertices.clear();
		backBuffer->Reset();
	}
}