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
	char GetNormalDirection() const;

private:
	Renderer::Quadric::IndexFunc drawStyle;
	GLenum normals;
	bool isReverseNormal;
	bool useTexture;

private:
	static const Dictionary<GLenum, Renderer::Quadric::IndexFunc> drawStyleTable;
};