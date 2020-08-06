#include "framework.h"
#include "SceneMenu.h"
#include "resource.h"
#include "Scene/SceneFactory.h"

UINT SceneMenu::currentSelected = 0;

std::unique_ptr<IScene> SceneMenu::Select( std::shared_ptr<IRenderer> renderer, HWND hWnd )
{
	return Select( renderer, hWnd, SceneFactory::defaultScene );
}

std::unique_ptr<IScene> SceneMenu::Select( std::shared_ptr<IRenderer> renderer, HWND hWnd, UINT resourceId )
{
    if ( currentSelected == resourceId )
    {
        return nullptr;
    }

    currentSelected = resourceId;
    CheckMenuItem( hWnd, resourceId );
    return SceneFactory::Create( renderer, resourceId );
}

void SceneMenu::CheckMenuItem( HWND hWnd, UINT resourceId )
{
    const auto hMenu = GetMenu( hWnd );
    const auto hScene = GetSubMenu( hMenu, 2 );
    const auto hNeHe = GetSubMenu( hScene, 1 );

    const auto first = SceneFactory::sceneRange.first;
    const auto last = SceneFactory::sceneRange.second;
    ::CheckMenuRadioItem( hScene, first, last, resourceId, MF_BYCOMMAND );
    ::CheckMenuRadioItem( hNeHe, first, last, resourceId, MF_BYCOMMAND );
}