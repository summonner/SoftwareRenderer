#pragma once
#include "IRenderer.h"

class GdiRenderer final : public IRenderer
{
private:
	GdiRenderer( const HWND hWnd, const int width, const int height );
public:
	static GdiRenderer* Create( const HWND hWnd );
	~GdiRenderer() override;

	void Clear() override;
	void Present( const HDC dc ) override;

private:
	const HWND hWnd;
	const int width;
	const int height;
};

