#include "framework.h"
#include "SutherlandHodgman.h"
#include "Renderer/Vertex.h"
#include "Renderer/Clipping/CustomClipPlanes.h"
#include "Renderer/Clipping/PlaneIterator.h"

// ref : https://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm
namespace Renderer
{
	std::vector<Vertex> SutherlandHodgman::ClipPolygon( const std::vector<Vertex>& vertices, const PlaneIterator& planes )
	{
		assert( vertices.size() >= 3 );
		auto in = vertices;
		std::vector<Vertex> out;
		out.reserve( vertices.size() * 2 );

		for ( const auto& plane : planes )
		{
			const auto* previous = &in[in.size() - 1];
			auto dotPrevious = plane.Dot( *previous );
			for ( const auto& current : in )
			{
				const auto dotCurrent = plane.Dot( current );

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

	std::vector<Vertex> SutherlandHodgman::ClipLine( const std::vector<Vertex>& vertices, const PlaneIterator& planes )
	{
		assert( vertices.size() == 2 );
		auto in = vertices;
		std::vector<Vertex> out;
		out.reserve( 2 );

		for ( const auto& plane : planes )
		{
			const auto& previous = in[0];
			const auto dotPrevious = plane.Dot( previous );

			if ( dotPrevious >= 0 )
			{
				out.push_back( previous );
			}

			const auto& current = in[1];
			const auto dotCurrent = plane.Dot( current );

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

	bool SutherlandHodgman::ClipPoint( const Vertex& vertex, const PlaneIterator& planes )
	{
		for ( const auto& plane : planes )
		{
			const auto dot = plane.Dot( vertex );
			if ( dot < 0 )
			{
				return false;
			}
		}

		return true;
	}

	void SutherlandHodgman::PushIntersect( const Vertex& previous, const Vertex& current, float dotPrevious, float dotCurrent, const IPlane& plane, std::vector<Vertex>& out )
	{
		const auto diff( previous.position - current.position );
		const auto denom = plane.DotWithDiff( previous, current );
		if ( denom != 0.0f )
		{
			if ( abs( dotPrevious * 2 ) > abs( denom ) )
			{
				const auto t1 = dotPrevious / denom;
				out.emplace_back( previous, current, t1 );
			}
			else
			{
				const auto t2 = plane.Dot( current ) / -denom;
				out.emplace_back( current, previous, t2 );
			}
		}
	}
}