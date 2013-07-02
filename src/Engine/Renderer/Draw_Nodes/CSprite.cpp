#include "CSprite.h"
#include "GLLoad/GLFuncs.h"


CSprite::CSprite():
CTextureNode(),
m_SpriteSize(0,0),
m_VBO(GL_ARRAY_BUFFER)
{
}

void CSprite::InitSprite(const std::string& aPathToTexture)
{
	if ( LoadTextureFromFile(aPathToTexture) )
	{
		SetSpriteSize( m_TextureSize );
	}
}

CSprite::~CSprite()
{

}

void CSprite::Render()
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

void CSprite::SetSpriteSize(const glm::uvec2& aSize)
{
	m_SpriteSize = aSize;
	SetBufferData();
}

glm::uvec2 CSprite::GetSpriteSize()
{
	return m_SpriteSize;
}

void CSprite::SetBufferData()
{
	const f32 w = (m_SpriteSize.x/2);
	const f32 h = (m_SpriteSize.y/2);

	m_QuadData.m_TopLeft 		=	D5_T2F_V3F(glm::vec2(0,0), glm::vec3(-w,h,1));
	m_QuadData.m_BottomLeft 	=	D5_T2F_V3F(glm::vec2(0,1), glm::vec3(-w,-h,1));
	m_QuadData.m_BottomRight 	=	D5_T2F_V3F(glm::vec2(1,0), glm::vec3(w,h,1));
	m_QuadData.m_TopRight 		=	D5_T2F_V3F(glm::vec2(1,1), glm::vec3(w,-h,1));

	m_VBO.LoadBufferData(&m_QuadData, 1, GL_STATIC_DRAW);

}
