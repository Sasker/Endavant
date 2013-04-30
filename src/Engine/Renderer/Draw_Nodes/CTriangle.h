#ifndef CTRIANGLE_H_
#define CTRIANGLE_H_

#include "Renderer/Base_Nodes/CBaseNode.h"
#include "Renderer/GL/CGLBufferObject.h"
#include <vector>
class CTriangle : public CBaseNode
{
public:
	CTriangle( const glm::vec2 &aPoint1, const glm::vec2 &aPoint2, const glm::vec2 &aPoint3, int z, const glm::vec3 &aColor);
	~CTriangle();

	virtual void Render();

private:

	D5_TRIANGLE<D5_C3F_V3F>						m_TriangleData;
	CGLBufferObject<D5_TRIANGLE<D5_C3F_V3F> >	m_VBO;
	glm::vec3 m_Color;
};


#endif /* CTRIANGLE_H_ */
