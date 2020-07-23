#include "framework.h"
#include "SampleScene.h"
#include "gl/glAdapter.h"
#include "Time.h"
#include "Renderer/IRenderer.h"

extern std::shared_ptr<IRenderer> _renderer;

SampleScene::SampleScene()
	: checker( Bitmap::Load( _T( "Data/Checker.bmp" ) ) )
{
}


SampleScene::~SampleScene()
{
}

void SampleScene::Init( std::shared_ptr<IRenderer> renderer )
{
}

float x = 0;
void SampleScene::Update( const Time& time )
{
	auto t = time.GetTimeFromStart();
	x = (sin( t ));// +1.f) * 0.5f;
}

void DrawScene( std::shared_ptr<const Bitmap> checker ) 
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	_renderer->BindTexture( nullptr );
	glTranslatef( -1.5f, 0.0f, -6.0f + 3 * 0 );
	glRotatef( x * -90.f, 0.f, 1.f, 0.f );
	glBegin( GL_TRIANGLES );
	glColor3f( 1.f, 0.f, 0.f );
	glTexCoord2f( 0.5f, 1.0f );
	glVertex3f( 0.f, 1.f, 0.f );

	glColor3f( 0.f, 1.f, 0.f );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f( -1.f, -1.f, 0.f );

	glColor3f( 0.f, 0.f, 1.f );
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f( 1.f, -1.f, 0.f );
	glEnd();

	glLoadIdentity();
	_renderer->BindTexture( checker );
	glTranslatef( 1.5f, 0.0f, -6.0f );
	glRotatef( x * 90.f, 1.f, 0.f, 0.f );
	glBegin( GL_QUADS );
	glColor3f( 1.0f, 0.5f, 0.5f );
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f( -1.0f, 1.0f, 0.0f );
	
	glColor3f( 0.5f, 0.5f, 0.5f );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f( -1.0f, -1.0f, 0.0f );

	glColor3f( 0.5f, 0.5f, 1.0f );
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f( 1.0f, -1.0f, 0.0f );

	glColor3f( 0.5f, 1.0f, 0.5f );
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f( 1.0f, 1.0f, 0.0f );
	glEnd();
}

void SampleScene::Render( std::shared_ptr<IRenderer> renderer ) const
{
	_renderer = renderer;
	DrawScene( checker );
	_renderer = nullptr;
	renderer->Present();
}