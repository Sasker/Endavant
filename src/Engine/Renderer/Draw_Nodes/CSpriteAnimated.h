#ifndef CSPRITEANIMATED_H_
#define CSPRITEANIMATED_H_
#include "Renderer/Base_Nodes/CTextureNode.h"


class CSpriteAnimated : public CTextureNode
{
public:
		CSpriteAnimated();

	void		InitSprite(const std::string &aPathToTexture);
	void		InitSprite(const std::string &aPathToTexture, s32 filas, s32 columnas);
	void		InitSprite(const std::string &aPathToTexture, s32 filas, s32 columnas, f32 speed);

	void		SetSpriteSize(const glm::uvec2 &aSize);
	glm::uvec2	GetSpriteSize();

	virtual ~CSpriteAnimated();

private:
	// Height and width of the sprite being rendered
	glm::uvec2	m_SpriteSize;

	s32 		m_indexAnimation;
	s32			m_filas;
	s32			m_columnas;
	f32			m_speedAnimation;

};

#endif /* CSPRITE_H_ */
