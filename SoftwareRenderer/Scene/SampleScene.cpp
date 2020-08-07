#include "framework.h"
#include "SampleScene.h"
#include "gl/glAdapter.h"
#include "Time.h"
#include "Util/Bitmap.h"
#include "Renderer/Texturing/Texture2D.h"
#include "Renderer/Texturing/TextureComponent.h"
#include "Renderer/Blending/BlendComponent.h"
#include "Renderer/Lighting/Light.h"
#include "Math/Degree.h"

void glBindTexture( GLenum target, std::shared_ptr<const Renderer::ITexture> texture )
{
	adapter->renderer->texture.Bind( texture );
}

SampleScene::SampleScene()
	: texture( nullptr )
	, light( new Renderer::Light() )
	, adapter( std::make_unique<glBridge>() )
{
	const auto bitmap = Bitmap::Load( _T( "Data/glass.bmp" ) );
	texture = std::make_shared<Renderer::Texture2D>( *bitmap, true );
	texture->SetWrapMode( TextureWrapMode::MirroredRepeat, TextureWrapMode::MirroredRepeat );
	texture->SetFilter( TextureMagFilter::Linear );
	texture->SetFilter( TextureMinFilter::LinearMipmapLinear );
}

SampleScene::~SampleScene()
{
}

void SampleScene::Init( const std::shared_ptr<IRenderer> renderer )
{
	adapter->Use( renderer.get(), []()
	{
		glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );
		//glEnable( GL_TEXTURE_2D );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE );
		glEnable( GL_CULL_FACE );
		glEnable( GL_LIGHTING );
	} );
	renderer->lighting.Add( light );
}

void SampleScene::OnResize( const std::shared_ptr<IRenderer> renderer, const int width, const int height )
{
	renderer->Viewport( 0, 0, width, height );
	renderer->Perspective( 45.f, (float)width / (float)height, 0.1f, 100.f );
}

float x = 0;
void SampleScene::Update( const Time& time )
{
	auto t = time.GetTimeFromStart();
//	t = .152f;
	x = (sin( t ));// +1.f) * 0.5f;
}

void SampleScene::DrawScene() const
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glEnable( GL_DEPTH_TEST );
	glDisable( GL_BLEND );
	//Floor();
	//Triangle();
	//Quad();
	Cube();
//	PointerTest();

	glDisable( GL_DEPTH_TEST );
	glEnable( GL_BLEND );
	glColor4f( 1, 1, 1, 0.5f );
}

void SampleScene::PointerTest() const
{
	const float v[]
	{
		-1.0f, -1.0f, 1.0f,		0.0f, 0.0f,
		1.0f, -1.0f, 1.0f,		1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,		0.0f, 1.0f,

		-1.0f, -1.0f, -1.0f,	1.0f, 0.0f,
		-1.0f, 1.0f, -1.0f,		1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,		0.0f, 1.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f,

		-1.0f, 1.0f, -1.0f,		0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,		0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,
		1.0f, 1.0f, -1.0f,		1.0f, 1.0f,

		-1.0f, -1.0f, -1.0f,	1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 1.0f,
		1.0f, -1.0f, 1.0f,		0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,		1.0f, 0.0f,

		1.0f, -1.0f, -1.0f,		1.0f, 0.0f,
		1.0f, 1.0f, -1.0f,		1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		1.0f, -1.0f, 1.0f,		0.0f, 0.0f,

		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,		1.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,		0.0f, 1.0f,
	};


	glLoadIdentity();
	glTranslatef( 0.0f, 0.0f, -5.f );
	glRotatef( x * 90.f, 1.0f, 0.0f, 0.0f );
	glRotatef( x * 90.f, 0.0f, 1.0f, 0.0f );
	glBindTexture( GL_TEXTURE_2D, texture );
	const auto stride = 5 * 4;
	glVertexPointer( 3, GL_FLOAT, stride, v );
	glTexCoordPointer( 2, GL_FLOAT, stride, v + 3 );
	glDrawArrays( GL_QUADS, 0, 6 * 4 );
}

void SampleScene::Floor() const
{
	glLoadIdentity();
	glBegin( GL_QUADS );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTranslatef( 0, -2, 15 * x - 10 );
	glColor3f( 1, 1, 1 );
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
	glTranslatef( -1.5f * 1, 0.0f, -6.0f + 6 * 0 );
	glRotatef( x * -90.f, 0.f, 1.f, 0.f );
	glBegin( GL_TRIANGLES );
	glColor4f( 1.f, 0.f, 0.f, 0.5f );
	glTexCoord2f( 0.5f, 1.0f );
	glVertex3f( 0.f, 1.f, 0.f );

	glColor4f( 0.f, 1.f, 0.f, 0.5f );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f( -1.f, -1.f, 0.f );

	glColor4f( 0.f, 0.f, 1.f, 0.5f );
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f( 1.f, -1.f, 0.f );
	glEnd();
}

void SampleScene::Quad() const
{
	glLoadIdentity();
	glBindTexture( GL_TEXTURE_2D, texture );
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

void SampleScene::Cube() const
{
	glLoadIdentity();
	glTranslatef( 0.0f, 0.0f, -5.f );
	glRotatef( x * 90.f, 1.0f, 0.0f, 0.0f );
	glRotatef( x * 90.f, 0.0f, 1.0f, 0.0f );
	glBindTexture( GL_TEXTURE_2D, texture );
	glBegin( GL_QUADS );
	// Front Face
	glNormal3f( 0.0f, 0.0f, 1.0f );
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 1.0f );
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, 1.0f );
	// Back Face
	glNormal3f( 0.0f, 0.0f, -1.0f );
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, -1.0f );
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, -1.0f );
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
	// Top Face
	glNormal3f( 0.0f, 1.0f, 0.0f );
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, -1.0f );
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, 1.0f, 1.0f );
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, -1.0f );
	// Bottom Face
	glNormal3f( 0.0f, -1.0f, 0.0f );
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 1.0f );
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
	// Right face
	glNormal3f( 1.0f, 0.0f, 0.0f );
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, -1.0f );
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, -1.0f );
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 1.0f, 1.0f, 1.0f );
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 1.0f, -1.0f, 1.0f );
	// Left Face
	glNormal3f( -1.0f, 0.0f, 0.0f );
	glTexCoord2f( 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, -1.0f );
	glTexCoord2f( 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
	glTexCoord2f( 1.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, 1.0f );
	glTexCoord2f( 0.0f, 1.0f ); glVertex3f( -1.0f, 1.0f, -1.0f );
	glEnd();
}

void SampleScene::Render( const std::shared_ptr<IRenderer> renderer ) const
{
	adapter->Use( renderer.get(), [this]() { SampleScene::DrawScene(); } );
	renderer->Present();
}