#include "CSprite.h"
#include "GLLoad/GLFuncs.h"


CSprite::CSprite():
CTextureNode(),
m_VBO(GL_ARRAY_BUFFER)
{
	m_Size = glm::vec2(0,0);
}

void CSprite::Init(const std::string& aPathToTexture)
{
	LoadTexture(aPathToTexture);

	m_Size.x = GetTextureWidth();
	m_Size.y = GetTextureHeight();

	SetBufferData();
}

void CSprite::Init(const std::string& aPathToTexture,const glm::vec2& aSize)
{
	LoadTexture(aPathToTexture);

	m_Size = aSize;

	SetBufferData();
}

CSprite::~CSprite()
{

}

void CSprite::Render()
{

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

void CSprite::SetBufferData()
{


	m_QuadData.m_TopLeft = D5_T2F_V3F(glm::vec2(0,0), glm::vec3(-m_Size.x/2, m_Size.y/2,1 ));
	m_QuadData.m_BottomLeft = D5_T2F_V3F(glm::vec2(0,1), glm::vec3(-m_Size.x/2,-m_Size.y/2,1));
	m_QuadData.m_BottomRight =  D5_T2F_V3F(glm::vec2(1,0), glm::vec3(m_Size.x/2,m_Size.y/2,1));
	m_QuadData.m_TopRight =  D5_T2F_V3F(glm::vec2(1,1), glm::vec3(m_Size.x/2,-m_Size.y/2,1));

	m_VBO.LoadBufferData(&m_QuadData, 1, GL_STATIC_DRAW);

}
