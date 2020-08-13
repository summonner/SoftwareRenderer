#include "framework.h"
#include "TexcoordFunc.h"
#include "Renderer/Vertex.h"
#include "Renderer/Matrix.h"

namespace Renderer
{
	TexcoordFunc::TexcoordFunc( const Vector4& plane )
		: plane( plane )
		, generateFunc( EyeLinear )
	{
	}

	TexcoordFunc::~TexcoordFunc()
	{
	}

	void TexcoordFunc::SetPlane( const Vector4& plane )
	{
		this->plane = plane;
	}

	void TexcoordFunc::operator =( Type type )
	{
		generateFunc = table[type];
	}

	float TexcoordFunc::operator ()( const Vertex& v, const Matrix& modelView ) const
	{
		return generateFunc( v, modelView, plane );
	}

	const Dictionary<TexcoordFunc::Type, TexcoordFunc::Func> TexcoordFunc::table
	{
		{ Type::EyeLinear, EyeLinear },
		{ Type::ObjectLinear, ObjectLinear },
		{ Type::Sphere, Sphere },
//		{ Type::Reflection, Reflection },
	};

	// ref : https://www.khronos.org/opengl/wiki/Mathematics_of_glTexGen
	float TexcoordFunc::EyeLinear( const Vertex& v, const Matrix& modelView, const Vector4& plane )
	{
		return v.position.Dot( plane );
	}

	float TexcoordFunc::ObjectLinear( const Vertex& v, const Matrix& modelView, const Vector4& plane )
	{
		const auto p = modelView.Inverse() * v.position;
		return p.Dot( plane );
	}

	float TexcoordFunc::Sphere( const Vertex& v, const Matrix& modelView, const Vector4& plane )
	{
		auto refl = Reflection( v );
		refl.z += 1;
		const auto m = 1 / (2 * refl.Length());
		refl = refl * m + 0.5f;
		return refl.Dot( plane );
	}

	Vector3 TexcoordFunc::Reflection( const Vertex& v )
	{
		const Vector3 p = v.position;
		return p - v.normal * 2 * p.Dot( v.normal );
	}

	/*Matrix4x4 TexcoordFunc::Reflection( const Vector3& n )
	{
		return Matrix4x4(
			 1 - 2 * n.x * n.x,			-2 * n.x * n.y,			-2 * n.x * n.z,		0,
				-2 * n.y * n.x,		 1 - 2 * n.y * n.y,			-2 * n.y * n.z,		0,
				-2 * n.z * n.x,			-2 * n.z * n.y,		 1 - 2 * n.z * n.z,		0,
							 0,						 0,						 0,		1
		);
	}*/

}