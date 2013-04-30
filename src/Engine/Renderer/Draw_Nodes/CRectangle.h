#ifndef CRECTANGLE_H_
#define CRECTANGLE_H_


#include "Renderer/Base_Nodes/CBaseNode.h"
#include "Renderer/GL/CGLBufferObject.h"

class CRectangle : public CBaseNode
{
public:
	CRectangle( const glm::vec2 &aSize, int z, const glm::vec3 &aColor);
	~CRectangle();

	virtual void Render();


private:
	D5_QUAD<D5_C3F_V3F>						m_QuadData;
	CGLBufferObject<D5_QUAD<D5_C3F_V3F> >	m_VBO;

	glm::vec2 m_Size;
	glm::vec3 m_Color;


	void	Test(); //Nomes per testeig..
};





#endif /* CRECTANGLE_H_ */
