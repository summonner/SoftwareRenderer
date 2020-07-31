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
			auto previous = in[in.size() - 1];
			auto dotPrevious = plane.Dot( Vector4( previous.position, 1.f ) );
			for ( const auto& current : in )
			{
				const auto dotCurrent = plane.Dot( Vector4( current.position, 1.f ) );

				if ( dotCurrent >= 0 )
				{
					if ( dotPrevious < 0 )
					{
						const Vector3 diff( previous.position - current.position );
						const auto denom = diff.Dot( plane );
						if ( denom != 0.0f )
						{
							const auto t = dotPrevious / diff.Dot( plane );
							out.emplace_back( previous, current, t );
						}
					}

					out.push_back( current );
				}
				else if ( dotPrevious >= 0 )
				{
					const Vector3 diff( previous.position - current.position );
					const auto denom = diff.Dot( plane );
					if ( denom != 0.0f )
					{
						const auto t = dotPrevious / diff.Dot( plane );
						out.emplace_back( previous, current, t );
					}
				}

				dotPrevious = dotCurrent;
				previous = current;
			}

			in = out;
			out.clear();
		}

		return in;
	}

	//SutherlandHodgmanClipping::Intersect();
}