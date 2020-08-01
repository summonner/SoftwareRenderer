#pragma once

namespace Renderer
{
	class IRasterizer;
	class IGeometry abstract
	{
	public:
		virtual ~IGeometry() {}

		virtual std::unique_ptr<IRasterizer> Clip() const abstract;
	};
}