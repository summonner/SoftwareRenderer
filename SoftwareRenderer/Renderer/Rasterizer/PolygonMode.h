#pragma once

namespace Renderer
{
	class PolygonMode final
	{
	public:
		enum class Mode
		{
			Fill,
			Line,
			Point,
		};

	public:
		PolygonMode();
		~PolygonMode();

		void Reset();
		Mode Get( bool isFront ) const;

	public:
		Mode front;
		Mode back;
	};
}

using PolygonMode = Renderer::PolygonMode::Mode;