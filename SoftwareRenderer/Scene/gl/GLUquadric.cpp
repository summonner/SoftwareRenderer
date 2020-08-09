#include "framework.h"
#include "GLUquadric.h"
#include "Renderer/IRenderer.h"

const Dictionary<GLenum, Renderer::Quadric::IndexFunc> GLUquadric::drawStyleTable
{
	{ GLU_FILL, Renderer::Quadric::Solid },
	{ GLU_LINE, Renderer::Quadric::Wire },
	{ GLU_SILHOUETTE, Renderer::Quadric::Wire },
	{ GLU_POINT, nullptr },
};

GLUquadric::GLUquadric()
	: drawStyle( drawStyleTable[GLU_FILL] )
{
}

GLUquadric::~GLUquadric()
{
}

void GLUquadric::SetNormals( GLenum normals )
{
}

void GLUquadric::SetTexture( GLboolean textureCoords )
{
}

void GLUquadric::SetOrientation( GLenum orientation )
{
}

void GLUquadric::SetDrawStyle( GLenum drawStyle )
{
	this->drawStyle = drawStyleTable[drawStyle];
}

void GLUquadric::Draw( IRenderer& renderer, const Renderer::Quadric& quadric, int slices, int stacks ) const
{
	const auto mesh = quadric.Build( drawStyle, slices, stacks );
	renderer.Draw( mesh );
}