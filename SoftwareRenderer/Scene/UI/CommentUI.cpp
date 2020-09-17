#include "framework.h"
#include "CommentUI.h"

UI CommentUI::ui( 640, 480 );

void CommentUI::Print( IRenderer& renderer, const char* comment )
{
	ui.Begin( renderer );
	ui.Text( renderer, Vector2( 10, 10 ), comment );
	ui.End( renderer );
}