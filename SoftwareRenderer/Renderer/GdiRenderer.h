#pragma once
#include "IRenderer.h"

class GdiRenderer final : public IRenderer
{
public:
	GdiRenderer( const HWND& hWnd );
	~GdiRenderer() override;

	void Clear() override;
	void Present( const HDC& dc ) override;

private:
	const HWND hWnd;
};

