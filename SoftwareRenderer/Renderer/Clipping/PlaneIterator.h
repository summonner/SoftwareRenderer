#pragma once
#include "PlaneInView.h"
#include "PlaneInClip.h"
#include "Util/IBaseIterator.h"

namespace Renderer
{
	class PlaneIterator final : public IBaseIterator<PlaneIterator, const IPlane&>
	{
	public:
		PlaneIterator( const std::vector<PlaneInView>& customPlanes, unsigned int current );
		~PlaneIterator();

		PlaneIterator begin() const;
		PlaneIterator end() const;

		bool operator !=( const PlaneIterator& other ) const;
		const PlaneIterator& operator++();
		const IPlane& operator *() const;

	private:
		const std::vector<PlaneInView>& customPlanes;
		unsigned int current;

		static const std::vector<PlaneInClip> staticPlanes;
	};
}