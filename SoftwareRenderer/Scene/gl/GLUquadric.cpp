#include "framework.h"
#include "GLUquadric.h"
#include "Renderer/IRenderer.h"

const Dictionary<GLenum, Renderer::Quadric::IndexFunc> GLUquadric::drawStyleTable
{
	{ GLU_FILL, &Renderer::Quadric::Solid },
	{ GLU_LINE, &Renderer::Quadric::Wire },
	{ GLU_SILHOUETTE, &Renderer::Quadric::Wire },
	{ GLU_POINT, nullptr },
};

GLUquadric::GLUquadric()
	: drawStyle( drawStyleTable[GLU_FILL] )
	, useTexture( true )
	, isReverseNormal( false )
	, normals( GLU_SMOOTH )
{
}

GLUquadric::~GLUquadric()
{
}

void GLUquadric::SetNormals( GLenum normals )
{
	if ( normals == GL_SMOOTH )
	{
		normals = GLU_SMOOTH;
	}

	this->normals = normals;
}

void GLUquadric::SetTexture( GLboolean textureCoords )
{
	useTexture = (textureCoords == GLU_TRUE);
}

void GLUquadric::SetOrientation( GLenum orientation )
{
	isReverseNormal = (orientation == GLU_INSIDE);
}

void GLUquadric::SetDrawStyle( GLenum drawStyle )
{
	this->drawStyle = drawStyleTable[drawStyle];
}

void GLUquadric::Draw( IRenderer& renderer, const Renderer::Quadric& quadric, int slices, int stacks ) const
{
	const ScopedShadeModel applyShadeModel( normals );

	const auto normalDirection = GetNormalDirection();
	const auto mesh = quadric.Build( drawStyle, slices, stacks, useTexture, normalDirection );
	renderer.Draw( mesh );
}

char GLUquadric::GetNormalDirection() const
{
	if ( normals == GLU_NONE )
	{
		return 0;
	}

	if ( isReverseNormal == true )
	{
		return -1;
	}
	else
	{
		return 1;
	}
}


GLUquadric::ScopedShadeModel::ScopedShadeModel( GLenum type )
{
	oldType = Renderer::ShadeModel::type;
	const auto useSmooth = (oldType == Renderer::ShadeModel::Type::Smooth)
						&& (type == GLU_SMOOTH);
	if ( useSmooth == true )
	{
		Renderer::ShadeModel::type = Renderer::ShadeModel::Type::Smooth;
	}
	else
	{
		Renderer::ShadeModel::type = Renderer::ShadeModel::Type::Flat;
	}
}

GLUquadric::ScopedShadeModel::~ScopedShadeModel()
{
	Renderer::ShadeModel::type = oldType;
}