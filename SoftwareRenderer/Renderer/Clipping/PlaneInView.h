#pragma once
#include "IPlane.h"

namespace Renderer
{
	class PlaneInView final : public IPlane
	{
	public:
		PlaneInView( const Vector4* coefficients );
		~PlaneInView() override;

		bool operator ==( const Vector4* coefficients ) const;
		float Dot( const Vertex& vertex ) const override;
		float DotWithDiff( const Vertex& v1, const Vertex& v2 ) const override;

	private:
		const Vector4* coefficients;
	};
}

