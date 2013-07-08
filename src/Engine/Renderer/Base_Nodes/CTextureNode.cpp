#include "CTextureNode.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"

// TODO: Load more than bitmaps (BMP)
// TODO: mipmaps?


CTextureNode::CTextureNode():
CBaseNode(),
m_TextureSize(0,0),
m_TextureRawSize(0,0),
m_PathToTexture(""),
m_VBO(GL_ARRAY_BUFFER)
{
}

CTextureNode::~CTextureNode()
{
}

bool CTextureNode::LoadTextureFromFile(const std::string& a_PathToTexture)
{
//	SDL_Surface* Surface = SDL_LoadBMP(a_PathToTexture.c_str());
	SDL_Surface* Surface = IMG_Load(a_PathToTexture.c_str());
	if (!Surface)
	{
		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_ERROR, LOGSUB_RESOURCES, "FAILED LOADING %s", a_PathToTexture.c_str() );
		return false;
	}

	bool retval = LoadTextureFromSurface(*Surface);
	SDL_FreeSurface(Surface);
	return retval;
}


bool CTextureNode::LoadTextureFromSurface(const SDL_Surface &aSurface)
{
	GLenum TextureFormat;

	switch(aSurface.format->BytesPerPixel)
	{
	case 3:
		if (aSurface.format->Rmask == 0x000000ff)
			TextureFormat = GL_RGB;
		else
			TextureFormat = GL_BGR;
		break;

	case 4:
		if (aSurface.format->Rmask == 0x000000ff)
			TextureFormat = GL_RGBA;
		else
			TextureFormat = GL_BGRA;
		break;

	default:
		return false;
	}

	m_TextureRawSize.x = aSurface.w;
	m_TextureRawSize.y = aSurface.h;
	m_GLTexture.InitWithData(aSurface.pixels,aSurface.format->BytesPerPixel,m_TextureRawSize.x,m_TextureRawSize.y,TextureFormat);

	m_TextureSize = m_TextureRawSize;
	SetVBOData();
	return true;



}

void CTextureNode::SetVBOData()
{
	const f32 w = (m_TextureSize.x/2);
	const f32 h = (m_TextureSize.y/2);

	m_QuadData.m_TopLeft 		=	D5_T2F_V3F(glm::vec2(0,0), glm::vec3(-w,h,1));
	m_QuadData.m_BottomLeft 	=	D5_T2F_V3F(glm::vec2(0,1), glm::vec3(-w,-h,1));
	m_QuadData.m_BottomRight 	=	D5_T2F_V3F(glm::vec2(1,0), glm::vec3(w,h,1));
	m_QuadData.m_TopRight 		=	D5_T2F_V3F(glm::vec2(1,1), glm::vec3(w,-h,1));

	m_VBO.LoadBufferData(&m_QuadData, 1, GL_STATIC_DRAW);

}

void CTextureNode::Render()
{
	// Check if the texture is loaded
	if (!m_GLTexture.IsLoaded() )
		return;


	glLoadIdentity();
	glTranslatef( m_PositionAbsolute.x, m_PositionAbsolute.y, m_PositionAbsolute.z);
	glRotatef( GetRotation() ,0.0f,0.0f,1.0f);


	m_GLTexture.Bind();
	m_VBO.BindBuffer();
	glTexCoordPointer(2,GL_FLOAT,5 * sizeof(GLfloat), ((GLubyte *) 0) );
	glVertexPointer(3,GL_FLOAT,5 * sizeof(GLfloat), ((GLubyte *) 0 + (2*sizeof(GLfloat))) );

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_TRIANGLE_STRIP,0,4);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	m_VBO.UnBindBuffer();
	m_GLTexture.UnBind();
	CBaseNode::Render();
}
