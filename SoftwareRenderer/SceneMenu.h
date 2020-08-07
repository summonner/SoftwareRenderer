#pragma once
class IScene;
class IRenderer;
class SceneMenu abstract final
{
public:
	static std::unique_ptr<IScene> Select( HWND hWnd );
	static std::unique_ptr<IScene> Select( HWND hWnd, UINT resourceId );

private:
	static void CheckMenuItem( HWND hWnd, UINT resourceId );

	static UINT currentSelected;
};

