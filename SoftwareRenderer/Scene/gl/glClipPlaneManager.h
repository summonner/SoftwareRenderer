#pragma once
#include "glAdapter.h"
#include "Renderer/Clipping/PlaneInView.h"
#include "Math/Vector4.hpp"

namespace Renderer
{
	class Matrix;
}

class glClipPlaneManager final
{
public:
	glClipPlaneManager();
	~glClipPlaneManager();

	void Set( GLenum plane, const GLdouble* equation, const Renderer::Matrix& modelView );
	const Vector4* Get( GLenum plane ) const;

private:
	const int maxPlanes = 6;
	std::vector<Vector4> planes;

	static int ToIndex( GLenum plane );
};

