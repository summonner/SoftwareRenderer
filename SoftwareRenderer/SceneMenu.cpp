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
    ::CheckMenuRadioItem( hMenu, ID_SCENE_NEHE, ID_SCENE_DEFAULT, resourceId, MF_BYCOMMAND );
}