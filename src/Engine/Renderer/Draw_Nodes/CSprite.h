#ifndef CSPRITE_H_
#define CSPRITE_H_
#include "Renderer/Base_Nodes/CTextureNode.h"
#include "Renderer/GL/CGLBufferObject.h"

class CSprite : public CTextureNode
{
public:
	CSprite();

	void		InitSprite(const std::string &aPathToTexture);

	void		SetSpriteSize(const glm::uvec2 &aSize);
	glm::uvec2	GetSpriteSize();

	virtual void Render();

	virtual ~CSprite();

private:
	void	SetBufferData();

	// Height and width of the sprite being rendered
	glm::uvec2	m_SpriteSize;

	D5_QUAD<D5_T2F_V3F>						m_QuadData;
	CGLBufferObject< D5_QUAD<D5_T2F_V3F> >	m_VBO;
};

#endif /* CSPRITE_H_ */
