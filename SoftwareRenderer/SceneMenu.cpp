#include "framework.h"
#include "SceneMenu.h"
#include "resource.h"
#include "Scene/SceneFactory.h"

UINT SceneMenu::currentSelected = 0;

std::unique_ptr<IScene> SceneMenu::Select( HWND hWnd )
{
	return Select( hWnd, SceneFactory::defaultScene );
}

std::unique_ptr<IScene> SceneMenu::Select( HWND hWnd, UINT resourceId )
{
    if ( currentSelected == resourceId )
    {
        return nullptr;
    }

    currentSelected = resourceId;
    CheckMenuItem( hWnd, resourceId );
    return SceneFactory::Create( resourceId );
}

void SceneMenu::CheckMenuItem( HWND hWnd, UINT resourceId )
{
    const auto hMenu = GetMenu( hWnd );
    const auto hScene = GetSubMenu( hMenu, 2 );
    const auto nehePos = GetMenuItemCount( hScene ) - 1;
    const auto hNeHe = GetSubMenu( hScene, nehePos );

    const auto first = SceneFactory::sceneRange.first;
    const auto last = SceneFactory::sceneRange.second;
    ::CheckMenuRadioItem( hScene, first, last, resourceId, MF_BYCOMMAND );
    ::CheckMenuRadioItem( hNeHe, first, last, resourceId, MF_BYCOMMAND );
}