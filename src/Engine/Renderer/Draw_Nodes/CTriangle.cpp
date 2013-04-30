#include "CTriangle.h"



CTriangle::CTriangle( const glm::vec2 &aPoint0, const glm::vec2 &aPoint1, const glm::vec2 &aPoint2, int z, const glm::vec3 &aColor):
CBaseNode(),
m_VBO(GL_ARRAY_BUFFER)
{
	//TODO: AIXO NO HO TINC CLAR... AQUESTA Z NO HA D'ESTAR AQUI SEGUR..
	m_Position.z = z;

	m_Color = aColor;

	// Inserting vertex data
	m_TriangleData.m_Point0 = D5_C3F_V3F(m_Color,glm::vec3(aPoint0,m_Position.z));
	m_TriangleData.m_Point1 = D5_C3F_V3F(m_Color,glm::vec3(aPoint1,m_Position.z));
	m_TriangleData.m_Point2 = D5_C3F_V3F(m_Color,glm::vec3(aPoint2,m_Position.z));

	// Load data to GPU
	m_VBO.LoadBufferData(&m_TriangleData, 1, GL_STATIC_DRAW);
}

CTriangle::~CTriangle()
{

}

void CTriangle::Render()
{

	glLoadIdentity();
	glTranslatef( m_PositionAbsolute.x, m_PositionAbsolute.y, m_PositionAbsolute.z);
	glRotatef( GetRotation() ,0.0f,0.0f,1.0f);


	m_VBO.BindBuffer();
	glColorPointer(3,GL_FLOAT,6 * sizeof(GLfloat), ((GLubyte *) 0) );
	glVertexPointer(3,GL_FLOAT,6 * sizeof(GLfloat), ((GLubyte *) 0 + (3*sizeof(GLfloat))) );

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_TRIANGLE_STRIP,0,3);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	m_VBO.UnBindBuffer();

	CBaseNode::Render();
}
