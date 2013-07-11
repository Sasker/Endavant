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
	EraseVBOData();
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

	if (retval)
	{
		m_TextureSize = m_TextureRawSize;
		SetVBOData();
	}
	return retval;
}

bool CTextureNode::LoadTextureFromFile(const std::string& aPath, const glm::uvec2 aSize)
{
	bool retval = LoadInternalTextureFromFile( aPath);

	if (retval)
	{
		m_TextureSize.x = aSize.x;
		m_TextureSize.y = aSize.y;
		SetVBOData();
	}

	return retval;
}

bool CTextureNode::LoadTextureFromFile(const std::string& aPath, const glm::uvec2 aSize, const u32 aCols, const u32 aRows, const u32 aNumFrames)
{
	bool retval = LoadInternalTextureFromFile( aPath);

	if (retval)
	{
		u32 ActualCol = 0;
		u32 ActualRow = 0;

		f32 ColSize = ((f32)m_TextureRawSize.x / (f32)aCols) / (f32)m_TextureRawSize.x;
		f32 RowSize = ((f32)m_TextureRawSize.y / (f32)aRows) / (f32)m_TextureRawSize.y;

		m_TextureSize.x = aSize.x;
		m_TextureSize.y = aSize.y;
		EraseVBOData();
		while (	m_VBO.size() < aNumFrames )
		{
			//u-v calculations
			f32 u_i = ColSize * ActualCol;
			f32 u_f = ColSize * (ActualCol + 1);
			f32 v_i = RowSize * ActualRow;
			f32 v_f = RowSize * (ActualRow + 1);

			SetVBOData( (m_VBO.size()), 0, 0, u_i, u_f, v_i, v_f );

			ActualCol++;
			if ( ActualCol >= aCols )
			{
				ActualCol = 0;
				ActualRow++;
			}
		}
	}
	return retval;
}

bool CTextureNode::LoadTextureFromFile(const std::string& aPath, const u32 aCols, const u32 aRows, const u32 aNumFrames)
{
	bool retval = LoadInternalTextureFromFile( aPath);

	if (retval)
	{
		u32 ActualCol = 0;
		u32 ActualRow = 0;

		f32 ColSize = ((f32)m_TextureRawSize.x / (f32)aCols) / (f32)m_TextureRawSize.x;
		f32 RowSize = ((f32)m_TextureRawSize.y / (f32)aRows) / (f32)m_TextureRawSize.y;

		m_TextureSize.x = ColSize * m_TextureRawSize.x;
		m_TextureSize.y = RowSize * m_TextureRawSize.y;
		EraseVBOData();
		while (	m_VBO.size() < aNumFrames )
		{
			//u-v calculations
			f32 u_i = ColSize * ActualCol;
			f32 u_f = ColSize * (ActualCol + 1);
			f32 v_i = RowSize * ActualRow;
			f32 v_f = RowSize * (ActualRow + 1);

			SetVBOData( (m_VBO.size()), 0, 0, u_i, u_f, v_i, v_f );

			ActualCol++;
			if ( ActualCol >= aCols )
			{
				ActualCol = 0;
				ActualRow++;
			}
		}
	}
	return retval;
}

bool CTextureNode::LoadTextureFromFile(const std::string& aPath, const u32 aNumFrames, const std::vector<glm::vec4>& aFrameData)
{
	if (aFrameData.size() < aNumFrames )
	{
		return false;
	}

	bool retval = LoadInternalTextureFromFile( aPath);

	if (retval)
	{
		EraseVBOData();
		while (	m_VBO.size() < aNumFrames )
		{
			u32 NumFrame = m_VBO.size();

			//u-v calculations
			f32 u_i = ((f32)aFrameData[NumFrame].x) / (f32)m_TextureRawSize.x ;
			f32 u_f = ((f32)aFrameData[NumFrame].z) / (f32)m_TextureRawSize.x ;
			f32 v_i = ((f32)aFrameData[NumFrame].y) / (f32)m_TextureRawSize.y ;
			f32 v_f = ((f32)aFrameData[NumFrame].w) / (f32)m_TextureRawSize.y ;

			SetVBOData( NumFrame, (aFrameData[NumFrame].z - aFrameData[NumFrame].x), (aFrameData[NumFrame].w - aFrameData[NumFrame].y), u_i, u_f, v_i, v_f );
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

void CTextureNode::EraseVBOData()
{
	for ( u32 count = 0; count < m_VBO.size(); count++ )
	{
		CGLBufferObject< D5_QUAD<D5_T2F_V3F> > *m_VBO_Element = m_VBO.back();
		delete (m_VBO_Element);
	}
	m_VBO.clear();
}

void CTextureNode::AddVBOData()
{
	CGLBufferObject< D5_QUAD<D5_T2F_V3F> > *m_VBO_Element = new CGLBufferObject< D5_QUAD<D5_T2F_V3F> >(GL_ARRAY_BUFFER);
	m_VBO.push_back( m_VBO_Element );
}


void CTextureNode::SetVBOData(const u32 aFrame, const u32 aW, const u32 aH, const f32 aU_i, const f32 aU_f, const f32 aV_i, const f32 aV_f )
{
	const f32 w = ((aW==0?m_TextureSize.x:aW)/2);
	const f32 h = ((aH==0?m_TextureSize.y:aH)/2);

	AddVBOData();

	m_QuadData.m_TopLeft 		=	D5_T2F_V3F(glm::vec2(aU_i,aV_i), glm::vec3(-w,h,1));
	m_QuadData.m_BottomLeft 	=	D5_T2F_V3F(glm::vec2(aU_i,aV_f), glm::vec3(-w,-h,1));
	m_QuadData.m_BottomRight 	=	D5_T2F_V3F(glm::vec2(aU_f,aV_i), glm::vec3(w,h,1));
	m_QuadData.m_TopRight 		=	D5_T2F_V3F(glm::vec2(aU_f,aV_f), glm::vec3(w,-h,1));

	GLuint BufferID = m_VBO[aFrame]->LoadBufferData(&m_QuadData, 1, GL_STATIC_DRAW);

	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_VIDEO, "VBO Object, BufferID: %u, Frame: %d, Data: (%d,%d) -> (%.02f,%.02f)(%.02f,%.02f)(%.02f,%.02f)(%.02f,%.02f)", (u32)BufferID, aFrame, (u32)(w*2), (u32)(h*2), m_QuadData.m_TopLeft.m_texCoord.x, m_QuadData.m_TopLeft.m_texCoord.y
		, m_QuadData.m_BottomLeft.m_texCoord.x, m_QuadData.m_BottomLeft.m_texCoord.y, m_QuadData.m_BottomRight.m_texCoord.x, m_QuadData.m_BottomRight.m_texCoord.y, m_QuadData.m_TopRight.m_texCoord.x, m_QuadData.m_TopRight.m_texCoord.y);

}

void CTextureNode::Render()
{
	// Check if the texture is loaded
	if ( m_GLTexture.IsLoaded() && m_Visible )
	{
		glLoadIdentity();
		glTranslatef( m_PositionAbsolute.x, m_PositionAbsolute.y, m_PositionAbsolute.z);
		glRotatef( GetRotation() ,0.0f,0.0f,1.0f);

		m_GLTexture.Bind();
		m_VBO[m_FrameNum]->BindBuffer();
		glTexCoordPointer(2,GL_FLOAT,5 * sizeof(GLfloat), ((GLubyte *) 0) );
		glVertexPointer(3,GL_FLOAT,5 * sizeof(GLfloat), ((GLubyte *) 0 + (2*sizeof(GLfloat))) );

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glDrawArrays(GL_TRIANGLE_STRIP,0,4);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		m_VBO[m_FrameNum]->UnBindBuffer();
		m_GLTexture.UnBind();
	}
	CBaseNode::Render();
}

void CTextureNode::Update(f64 dt)
{
	CBaseNode::Update( dt);
}

