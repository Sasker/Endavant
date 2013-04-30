#ifndef CSPRITE_H_
#define CSPRITE_H_
#include "Renderer/Base_Nodes/CTextureNode.h"
#include "Renderer/GL/CGLBufferObject.h"

class CSprite : public CTextureNode
{
public:
	CSprite();

	void	Init(const std::string &aPathToTexture);
	void	Init(const std::string &aPathToTexture, const glm::vec2 &aSize);

	virtual void Render();

	virtual ~CSprite();
private:
	void	SetBufferData();


	glm::vec2	m_Size;

	D5_QUAD<D5_T2F_V3F>						m_QuadData;
	CGLBufferObject< D5_QUAD<D5_T2F_V3F> >	m_VBO;
};

#endif /* CSPRITE_H_ */
