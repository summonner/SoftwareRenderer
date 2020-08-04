#include "framework.h"
#include "SutherlanHodgman.h"
#include "Renderer/Vertex.h"
#include "Math/Vector4.hpp"

// ref : https://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm
namespace Renderer
{
	const std::vector<Vector4> SutherlandHodgman::clipPlanes = 
	{
		{ 1, 0, 0, 1 },
		{ -1, 0, 0, 1 },
		{ 0, 1, 0, 1 },
		{ 0, -1, 0, 1 },
		{ 0, 0, 1, 1 },
		{ 0, 0, -1, 1 },
	};

	std::vector<Vertex> SutherlandHodgman::ClipPolygon( const std::vector<Vertex>& vertices )
	{
		assert( vertices.size() >= 3 );
		auto in = vertices;
		std::vector<Vertex> out;
		out.reserve( vertices.size() * 2 );

		for ( const auto& plane : clipPlanes )
		{
			const auto* previous = &in[in.size() - 1];
			auto dotPrevious = plane.Dot( previous->position );
			for ( const auto& current : in )
			{
				const auto dotCurrent = plane.Dot( current.position );

				if ( dotCurrent * dotPrevious < 0 )
				{
					PushIntersect( *previous, current, dotPrevious, dotCurrent, plane, out );
				}

				if ( dotCurrent >= 0 )
				{
					out.push_back( current );
				}

				dotPrevious = dotCurrent;
				previous = &current;
			}

			if ( out.size() <= 0 )
			{
				return out;
			}

			std::swap( in, out );
			out.clear();
		}

		return in;
	}

	std::vector<Vertex> SutherlandHodgman::ClipLine( const std::vector<Vertex>& vertices )
	{
		assert( vertices.size() == 2 );
		auto in = vertices;
		std::vector<Vertex> out;
		out.reserve( 2 );

		for ( const auto& plane : clipPlanes )
		{
			const auto& previous = in[0];
			const auto dotPrevious = plane.Dot( previous.position );

			if ( dotPrevious >= 0 )
			{
				out.push_back( previous );
			}

			const auto& current = in[1];
			const auto dotCurrent = plane.Dot( current.position );

			if ( dotPrevious * dotCurrent < 0 )
			{
				PushIntersect( previous, current, dotPrevious, dotCurrent, plane, out );
			}

			if ( dotCurrent >= 0 )
			{
				out.push_back( current );
			}

			if ( out.size() <= 0 )
			{
				return out;
			}

			std::swap( in, out );
			out.clear();
		}

		return in;
	}

	bool SutherlandHodgman::ClipPoint( const Vertex& vertex )
	{
		for ( const auto& plane : clipPlanes )
		{
			const auto dot = plane.Dot( vertex.position );
			if ( dot < 0 )
			{
				return false;
			}
		}

		return true;
	}

	void SutherlandHodgman::PushIntersect( const Vertex& previous, const Vertex& current, float dotPrevious, float dotCurrent, const Vector4& plane, std::vector<Vertex>& out )
	{
		const auto diff( previous.position - current.position );
		const auto denom = diff.Dot( plane );
		if ( denom != 0.0f )
		{
			const auto t1 = dotPrevious / denom;
			const auto t2 = plane.Dot( current.position ) / -denom;
			const auto v1 = Vector4::Lerp( previous.position, current.position, t1 );
			const auto v2 = Vector4::Lerp( current.position, previous.position, t2 );
			if ( abs( dotPrevious * 2 ) > abs( denom ) )
			{
				out.emplace_back( previous, current, t1 );
			}
			else
			{
				out.emplace_back( current, previous, t2 );
			}
		}
	}
}