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
	const auto bitmap = Bitmap::Load( _T( "Data/Checker.bmp" ) );
	checker = std::make_shared<Renderer::Texture2D>( *bitmap, true );
	checker->SetWrapMode( TextureWrapMode::MirroredRepeat, TextureWrapMode::MirroredRepeat );
	checker->SetFilter( TextureMagFilter::Linear );
	checker->SetFilter( TextureMinFilter::LinearMipmapLinear );
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

	Floor();
}

void SampleScene::Floor() const
{
	glLoadIdentity();
	glBegin( GL_QUADS );
	glBindTexture( GL_TEXTURE_2D, checker );
	glTranslatef( 0, -2, 15 * x - 10 );
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -10, 0, -10 );
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -10, 0, 10 );
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 10, 0, 10 );
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 10, 0, -10 );
	glEnd();
}

void SampleScene::Triangle() const
{
	glLoadIdentity();
	glBindTexture( GL_TEXTURE_2D, 0 );
	glTranslatef( -1.5f * 0, 0.0f, -6.0f + 6 * x );
	glRotatef( 0 * -90.f, 0.f, 1.f, 0.f );
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
}

void SampleScene::Quad() const
{
	glLoadIdentity();
	glBindTexture( GL_TEXTURE_2D, checker );
	glTranslatef( 1.5f * (1 - x), 0.0f, -6.0f + 5.5f * 0 );
	glScalef( x, x, 1 );
//	glRotatef( x * 90.f, 1.f, 0.f, 0.f );
	glBegin( GL_QUADS );
	auto min = -0.f;
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