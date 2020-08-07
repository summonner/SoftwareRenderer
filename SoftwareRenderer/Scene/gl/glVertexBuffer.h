#pragma once
#include "glBuffer.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

struct glVertexBuffer
{
	Renderer::Vertex operator []( int i ) const;

	std::unique_ptr<IBuffer<Vector4>> vertices;
	std::unique_ptr<IBuffer<Vector2>> texcoords;
	std::unique_ptr<IBuffer<Vector4>> colors;
	std::unique_ptr<IBuffer<Vector3>> normals;
};

