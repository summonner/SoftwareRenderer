#include "framework.h"
#include "SceneMenu.h"
#include "resource.h"
#include "Scene/SceneFactory.h"

UINT SceneMenu::currentSelected = 0;
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
    auto hMenu = GetMenu( hWnd );
    auto hScene = GetSubMenu( hMenu, 2 );
    auto hNeHe = GetSubMenu( hScene, 1 );

    auto first = ID_SCENE_NEHE;
    auto last = ID_NEHE_LESSON8;
    ::CheckMenuRadioItem( hScene, first, last, resourceId, MF_BYCOMMAND );
    ::CheckMenuRadioItem( hNeHe, first, last, resourceId, MF_BYCOMMAND );
}