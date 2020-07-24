#include "framework.h"
#include "SampleScene.h"
#include "gl/glAdapter.h"
#include "Time.h"
#include "Util/Bitmap.h"
#include "Renderer/Texturing/Texture2D.h"

void glBindTexture( GLenum target, std::shared_ptr<const Renderer::ITexture> texture )
{
	_renderer->BindTexture( texture );
}

SampleScene::SampleScene( std::shared_ptr<IRenderer> renderer )
	: checker( nullptr )
{
	auto bitmap = Bitmap::Load( _T( "Data/Crate.bmp" ) );
	checker = std::make_shared<Renderer::Texture2D>( bitmap.get() );
	checker->SetWrapMode( Renderer::ITexture::WrapMode::MirroredRepeat, Renderer::ITexture::WrapMode::MirroredRepeat );
}


SampleScene::~SampleScene()
{
}

float x = 0;
void SampleScene::Update( const Time& time )
{
	auto t = time.GetTimeFromStart();
	x = (sin( t ));// +1.f) * 0.5f;
}

void SampleScene::DrawScene() const
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	glBindTexture( GL_TEXTURE_2D, 0 );
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
	glBindTexture( GL_TEXTURE_2D, checker );
	glTranslatef( 1.5f, 0.0f, -6.0f );
	glRotatef( x * 90.f, 1.f, 0.f, 0.f );
	glBegin( GL_QUADS );
	auto min = -3.f;
	auto max = -min + 1.f;
//	glColor3f( 1.0f, 0.5f, 0.5f );
	glTexCoord2f( min, max );
	glVertex3f( -1.0f, 1.0f, 0.0f );
	
//	glColor3f( 0.5f, 0.5f, 0.5f );
	glTexCoord2f( min, min );
	glVertex3f( -1.0f, -1.0f, 0.0f );

//	glColor3f( 0.5f, 0.5f, 1.0f );
	glTexCoord2f( max, min );
	glVertex3f( 1.0f, -1.0f, 0.0f );

//	glColor3f( 0.5f, 1.0f, 0.5f );
	glTexCoord2f( max, max );
	glVertex3f( 1.0f, 1.0f, 0.0f );
	glEnd();
}

void SampleScene::Render( std::shared_ptr<IRenderer> renderer ) const
{
	_renderer = renderer;
	DrawScene();
	_renderer = nullptr;
	renderer->Present();
}