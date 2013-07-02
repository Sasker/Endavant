#ifndef CSPRITE_H_
#define CSPRITE_H_
#include "Renderer/Base_Nodes/CTextureNode.h"


class CSprite : public CTextureNode
{
public:
	CSprite();

	void		InitSprite(const std::string &aPathToTexture);

	void		SetSpriteSize(const glm::uvec2 &aSize);
	glm::uvec2	GetSpriteSize();

	virtual ~CSprite();

private:
	// Height and width of the sprite being rendered
	glm::uvec2	m_SpriteSize;


};

#endif /* CSPRITE_H_ */
