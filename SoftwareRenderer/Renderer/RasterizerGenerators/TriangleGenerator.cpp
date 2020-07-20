#include "framework.h"
#include "TriangleGenerator.h"
#include "Renderer/Rasterizer/Triangle.h"
#include "Renderer/Vertex.h"
#include "Math/Vector3.hpp"

#undef max
#undef min
#define max std::max
#define min std::min

namespace Renderer
{
	void TriangleGenerator::Triangles( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers )
	{
		auto lastIndex = endIndex - 2;
		for ( auto i = startIndex; i < lastIndex; i += 3 )
		{
			outRasterizers.push_back( std::make_unique<Triangle>( vertices[i], vertices[i + 1], vertices[i + 2] ) );
		}
	}

	void TriangleGenerator::TriangleStrip( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers )
	{
		auto lastIndex = endIndex - 3;
		auto i = startIndex;
		for ( ; i < lastIndex; i += 2 )
		{
			Build( vertices[i], vertices[i + 1], vertices[i + 2], outRasterizers );
			Build( vertices[i + 2], vertices[i + 1], vertices[i + 3], outRasterizers );
		}

		if ( i == lastIndex )
		{
			Build( vertices[i], vertices[i + 1], vertices[i + 2], outRasterizers );
		}
	}

	void TriangleGenerator::TriangleFan( VertexBuffer vertices, int startIndex, int endIndex, IRasterizerList& outRasterizers )
	{
		auto lastIndex = endIndex - 1;
		for ( auto i = startIndex + 1; i < lastIndex; i += 1 )
		{
			Build( vertices[startIndex], vertices[i], vertices[i + 1], outRasterizers );
		}
	}

	void TriangleGenerator::Build( const Vertex& a, const Vertex& b, const Vertex& c, IRasterizerList& outRasterizers )
	{
		if ( CheckClipped( a.clip, b.clip, c.clip ) == false )
		{
			return;
		}

		outRasterizers.emplace_back( std::make_unique<Triangle>( a, b, c ) );
	}

	bool TriangleGenerator::CheckClipped( const Vector3& v0, const Vector3& v1, const Vector3& v2 )
	{
		auto f0 = v1 - v0;
		auto f1 = v2 - v1;
		auto f2 = v0 - v2;

		float p0, p1, p2, r;
		// a00
		p0 = v0.z * v1.y - v0.y * v1.z;
		p2 = v2.z * (v1.y - v0.y) - v2.z * (v1.z - v0.z);
		r = abs( f0.z ) + abs( f0.y );
		if ( max( -max( p0, p2 ), min( p0, p2 ) ) > r ) return false;

		// a01
		p0 = -v0.y * v2.z + v0.y * v1.z + v0.z * v2.y - v0.z * v1.y;
		p1 = -v1.y * v2.z + v1.z * v2.y;
		r = abs( f1.z ) + abs( f1.y );
		if ( max( -max( p0, p1 ), min( p0, p1 ) ) > r ) return false;

		// a02
		p0 = v0.y * v2.z - v0.z * v2.y;
		p1 = -v1.y * v0.z + v1.y * v2.z + v1.z * v0.y - v1.z * v2.y;
		r = abs( f2.z ) + abs( f2.y );
		if ( max( -max( p0, p1 ), min( p0, p1 ) ) > r ) return false;

		// a10
		p0 = v0.x * v1.z - v0.z * v1.x;
		p2 = v2.x * v1.z - v2.x * v0.z - v2.z * v1.x + v2.z * v0.x;
		r = abs( f0.z ) + abs( f0.x );
		if ( max( -max( p0, p2 ), min( p0, p2 ) ) > r ) return false;

		// a11
		p0 = v0.x * v2.z - v0.x * v1.z - v0.z * v2.x + v0.z * v1.x;
		p1 = v1.x * v2.z - v1.z * v2.x;
		r = abs( f1.z ) + abs( f1.x );
		if ( max( -max( p0, p1 ), min( p0, p1 ) ) > r ) return false;

		// a12
		p0 = -v0.x * v2.z + v0.z * v2.x;
		p1 = v1.x * v0.z - v1.x * v2.z - v1.z * v0.x + v1.z * v2.x;
		r = abs( f2.z ) + abs( f2.x );
		if ( max( -max( p0, p1 ), min( p0, p1 ) ) > r ) return false;

		// a20
		p0 = -v0.x * v1.y + v0.y * v1.x;
		p2 = -v2.x * v1.y + v2.x * v0.y + v2.y * v1.x - v2.y * v0.x;
		r = abs( f0.y ) + abs( f0.x );
		if ( max( -max( p0, p2 ), min( p0, p2 ) ) > r ) return false;

		// a21
		p0 = -v0.x * v2.y + v0.x * v1.y + v0.y * v2.x - v0.y * v1.x;
		p1 = -v1.x * v2.y + v1.y * v2.x;
		r = abs( f1.y ) + abs( f1.x );
		if ( max( -max( p0, p1 ), min( p0, p1 ) ) > r ) return false;

		// a22
		p0 = v0.x * v2.y - v0.y * v2.x;
		p1 = v1.x * v0.y + v1.x * v2.y + v1.y * v0.x - v1.y * v2.x;
		r = abs( f2.y ) + abs( f2.x );
		if ( max( -max( p0, p1 ), min( p0, p1 ) ) > r ) return false;

		// aabb axises
		if ( max( { v0.x, v1.x, v2.x } ) < -1 || min( { v0.x, v1.x, v2.x } ) > 1 ) return false;
		if ( max( { v0.y, v1.y, v2.y } ) < -1 || min( { v0.y, v1.y, v2.y } ) > 1 ) return false;
		if ( max( { v0.z, v1.z, v2.z } ) < -1 || min( { v0.z, v1.z, v2.z } ) > 1 ) return false;

		// triangle normal
		auto n = f0.Cross( f1 );
		auto d = n.Dot( v0 );
		r = abs( n.x ) + abs( n.y ) + abs( n.z );
		auto s = abs( d );
		return s <= r;
	}
}