#include "CTextureNode.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"

// TODO: mipmaps?


CTextureNode::CTextureNode():
CBaseNode(),
m_TextureSize(0,0),
m_TextureRawSize(0,0),
m_PathToTexture(""),
m_FrameNum(0)
{
	CGLBufferObject< D5_QUAD<D5_T2F_V3F> > m_VBO_Element(GL_ARRAY_BUFFER);

	m_VBO.clear();
	m_VBO.push_back( m_VBO_Element );
}

CTextureNode::~CTextureNode()
{
}

bool CTextureNode::LoadInternalTextureFromFile(const std::string& aPath)
{
	SDL_Surface* Surface = IMG_Load(aPath.c_str());
	if (!Surface)
	{
		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_ERROR, LOGSUB_RESOURCES, "FAILED LOADING %s", aPath.c_str() );
		return false;
	}

	bool retval = LoadTextureFromSurface(*Surface);
	SDL_FreeSurface(Surface);

	return retval;
}

bool CTextureNode::LoadTextureFromFile(const std::string& aPath)
{
	bool retval = LoadInternalTextureFromFile( aPath);

	m_TextureSize = m_TextureRawSize;
	SetVBOData();

	return retval;
}

bool CTextureNode::LoadTextureFromFile(const std::string& aPath, glm::uvec2 aSize)
{
	bool retval = LoadInternalTextureFromFile( aPath);

	m_TextureSize.x = aSize.x;
	m_TextureSize.y = aSize.y;
	SetVBOData();

	return retval;
}

bool CTextureNode::LoadTextureFromFile(const std::string& aPath, glm::uvec2 aSize, u32 aCols, u32 aRows, u32 aNumFrames)
{
	bool retval = LoadInternalTextureFromFile( aPath);
	u32 ActualCol = 0;
	u32 ActualRow = 0;

	f32 ColSize = ((f32)m_TextureRawSize.x / (f32)aCols) / (f32)m_TextureRawSize.x;
	f32 RowSize = ((f32)m_TextureRawSize.y / (f32)aRows) / (f32)m_TextureRawSize.y;

	m_TextureSize.x = aSize.x;
	m_TextureSize.y = aSize.y;
	m_VBO.clear();
	while (	m_VBO.size() < aNumFrames )
	{
		CGLBufferObject< D5_QUAD<D5_T2F_V3F> > m_VBO_Element(GL_ARRAY_BUFFER);
		m_VBO.push_back( m_VBO_Element );

		//u-v calculations
		f32 u_i = ColSize * ActualCol;
		f32 u_f = ColSize * (ActualCol + 1);
		f32 v_i = RowSize * ActualRow;
		f32 v_f = RowSize * (ActualRow + 1);

		SetVBOData( (m_VBO.size() - 1), u_i, u_f, v_i, v_f );

		ActualCol++;
		if ( ActualCol >= aCols )
		{
			ActualCol = 0;
			ActualRow++;
		}
	}
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

	return true;
}

void CTextureNode::SetVBOData(u32 aFrame, f32 aU_i, f32 aU_f, f32 aV_i, f32 aV_f )
{
	const f32 w = (m_TextureSize.x/2);
	const f32 h = (m_TextureSize.y/2);

	m_QuadData.m_TopLeft 		=	D5_T2F_V3F(glm::vec2(aU_i,aV_i), glm::vec3(-w,h,1));
	m_QuadData.m_BottomLeft 	=	D5_T2F_V3F(glm::vec2(aU_i,aV_f), glm::vec3(-w,-h,1));
	m_QuadData.m_BottomRight 	=	D5_T2F_V3F(glm::vec2(aU_f,aV_i), glm::vec3(w,h,1));
	m_QuadData.m_TopRight 		=	D5_T2F_V3F(glm::vec2(aU_f,aV_f), glm::vec3(w,-h,1));

	m_VBO[aFrame].LoadBufferData(&m_QuadData, 1, GL_STATIC_DRAW);

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
	m_VBO[m_FrameNum].BindBuffer();
	glTexCoordPointer(2,GL_FLOAT,5 * sizeof(GLfloat), ((GLubyte *) 0) );
	glVertexPointer(3,GL_FLOAT,5 * sizeof(GLfloat), ((GLubyte *) 0 + (2*sizeof(GLfloat))) );

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_TRIANGLE_STRIP,0,4);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	m_VBO[m_FrameNum].UnBindBuffer();
	m_GLTexture.UnBind();
	CBaseNode::Render();
}

