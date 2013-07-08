#ifndef CSPRITEANIMATED_H_
#define CSPRITEANIMATED_H_
#include "Renderer/Base_Nodes/CTextureNode.h"


class CSpriteAnimated : public CTextureNode
{
public:
		CSpriteAnimated();

	void		InitSprite(const std::string &aPathToTexture);

	void		SetSpriteSize(const glm::uvec2 &aSize);
	glm::uvec2	GetSpriteSize();

	virtual ~CSpriteAnimated();

private:
	// Height and width of the sprite being rendered
	glm::uvec2	m_SpriteSize;


};

#endif /* CSPRITE_H_ */
