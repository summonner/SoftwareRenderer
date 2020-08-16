#pragma once
#include "PlaneInView.h"

namespace Renderer
{
	class Vertex;
	class PlaneIterator;
	class CustomClipPlanes final
	{
	public:
		CustomClipPlanes();
		~CustomClipPlanes();

		void Add( const Vector4* coefficients );
		void Remove( const Vector4* coefficients );

		operator const PlaneIterator() const;

	private:
		std::vector<PlaneInView> planes;
	};
}