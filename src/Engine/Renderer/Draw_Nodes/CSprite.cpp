#include "CSprite.h"
#include "GLLoad/GLFuncs.h"


CSprite::CSprite():
CTextureNode(),
m_SpriteSize(0,0)
{
}

void CSprite::InitSprite(const std::string& aPathToTexture)
{
	LoadTextureFromFile(aPathToTexture);
}

CSprite::~CSprite()
{
}

void CSprite::SetSpriteSize(const glm::uvec2& aSize)
{
	m_SpriteSize = aSize;
}

glm::uvec2 CSprite::GetSpriteSize()
{
	return m_SpriteSize;
}


