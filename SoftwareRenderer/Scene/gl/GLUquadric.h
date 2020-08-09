#pragma once
#include "glAdapter.h"
#include "Renderer/Mesh/Cylinder.h"
#include "Renderer/Mesh/Sphere.h"
#include "Renderer/Mesh/Disc.h"

class GLUquadric final
{
public:
	GLUquadric();
	~GLUquadric();

	void SetNormals( GLenum normals );
	void SetTexture( GLboolean textureCoords );
	void SetOrientation( GLenum orientation );
	void SetDrawStyle( GLenum drawStyle );
	void Draw( IRenderer& renderer, const Renderer::Quadric& quadric, int slices, int stacks ) const;

private:
	Renderer::Quadric::IndexFunc drawStyle;

private:
	static const Dictionary<GLenum, Renderer::Quadric::IndexFunc> drawStyleTable;
};