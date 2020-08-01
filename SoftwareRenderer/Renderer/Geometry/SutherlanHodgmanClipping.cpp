#include "framework.h"
#include "SutherlanHodgmanClipping.h"
#include "Renderer/Vertex.h"
#include "Math/Vector4.hpp"

// ref : https://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm
namespace Renderer
{
	const std::vector<Vector4> SutherlandHodgmanClipping::clipPlanes = 
	{
		{ 1, 0, 0, 1 },
		{ -1, 0, 0, 1 },
		{ 0, 1, 0, 1 },
		{ 0, -1, 0, 1 },
		{ 0, 0, 1, 1 },
		{ 0, 0, -1, 1 },
	};

	std::vector<Vertex> SutherlandHodgmanClipping::Clip( const std::vector<Vertex>& vertices )
	{
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
					PushIntersect( *previous, current, dotPrevious, plane, out );
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

	void SutherlandHodgmanClipping::PushIntersect( const Vertex& previous, const Vertex& current, float dotPrevious, const Vector4& plane, std::vector<Vertex>& out )
	{
		const auto diff( previous.position - current.position );
		const auto denom = diff.Dot( plane );
		if ( denom != 0.0f )
		{
			const auto t = dotPrevious / denom;
			out.emplace_back( previous, current, t );
		}
	}
}