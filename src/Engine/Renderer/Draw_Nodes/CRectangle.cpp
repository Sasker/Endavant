#include "CRectangle.h"



CRectangle::CRectangle( const glm::vec2 &aSize, int z, const glm::vec3 &aColor):
CBaseNode(),
m_VBO(GL_ARRAY_BUFFER)
{
	m_Size = aSize;
	m_Position.z = z;
	m_Color = aColor;

	m_QuadData.m_TopLeft = D5_C3F_V3F(aColor, glm::vec3(-(m_Size.x/2) , (m_Size.y / 2),m_Position.z));
	m_QuadData.m_BottomLeft = D5_C3F_V3F(aColor, glm::vec3(-(m_Size.x/2) , -(m_Size.y / 2),m_Position.z));
	m_QuadData.m_BottomRight = D5_C3F_V3F(aColor, glm::vec3((m_Size.x/2) , (m_Size.y / 2),m_Position.z));
	m_QuadData.m_TopRight = D5_C3F_V3F(aColor, glm::vec3((m_Size.x/2) , -(m_Size.y / 2),m_Position.z));

	m_VBO.LoadBufferData(&m_QuadData, 1, GL_STATIC_DRAW);

}

CRectangle::~CRectangle()
{

}

void CRectangle::Render()
{
	if ( m_Visible )
	{
		glLoadIdentity();
		glTranslatef( m_PositionAbsolute.x, m_PositionAbsolute.y, m_PositionAbsolute.z);
		glRotatef( GetRotation() ,0.0f,0.0f,1.0f);


		m_VBO.BindBuffer();
		glColorPointer(3,GL_FLOAT,6 * sizeof(GLfloat), ((GLubyte *) 0) );
		glVertexPointer(3,GL_FLOAT,6 * sizeof(GLfloat), ((GLubyte *) 0 + (3*sizeof(GLfloat))) );

		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glDrawArrays(GL_TRIANGLE_STRIP,0,4);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		m_VBO.UnBindBuffer();
	}
	CBaseNode::Render();
}

void CRectangle::Test()
{
// TEST VERTEX ARRAYS No fer cas.. son proves..
	/*
	GLuint VBO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	GLfloat vertexData[3][6];

	vertexData[0][0]  = 1.0F; vertexData[0][1]  = 0.0F; vertexData[0][2]  = 1.0F; //c1
	vertexData[0][3]  = 0.0F; vertexData[0][4]  = 0.0F; vertexData[0][5]  = 1.0F; //v1

	vertexData[1][0]  = 1.0F; vertexData[1][1]  = 1.0F; vertexData[1][2]  = 1.0F; //c1
	vertexData[1][3]  = 100.0F; vertexData[1][4]  = 0.0F; vertexData[1][5]  = 1.0F; //v1

	vertexData[2][0]  = 1.0F; vertexData[2][1]  = 0.0F; vertexData[2][2]  = 1.0F; //c1
	vertexData[2][3]  = 100.0F; vertexData[2][4]  = 100.0F; vertexData[2][5]  = 1.0F; //v1



	glBufferData(GL_ARRAY_BUFFER, 3*6 * sizeof(GLfloat), &vertexData[0][0], GL_STATIC_DRAW);

	//En teoria es podria fer:
	//glInterleavedArrays(GL_C3F_V3F, 0, ((GLubyte *) + 0));
	//Pero per a fer-ho generic i a part de que glInterleavedArrays esta deprecat fem el que hi ha
	//a continuacio:

	glVertexPointer(3,GL_FLOAT,6 * sizeof(GLfloat), ((GLubyte *) 0 + (3*sizeof(GLfloat))) );
	glColorPointer(3,GL_FLOAT,6 * sizeof(GLfloat), ((GLubyte *) 0) );
	/// Especifiquem que hi ha al array
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState( GL_VERTEX_ARRAY);

	glDrawArrays(GL_TRIANGLES,0,3);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState( GL_VERTEX_ARRAY);

	glDeleteBuffers(1, &VBO);
	*/
}


