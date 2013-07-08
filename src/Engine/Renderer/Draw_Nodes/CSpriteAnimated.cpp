#include "CSpriteAnimated.h"
#include "GLLoad/GLFuncs.h"


CSpriteAnimated::CSpriteAnimated():
CTextureNode(),
m_SpriteSize(0,0)
{
}

void CSpriteAnimated::InitSprite(const std::string& aPathToTexture)
{
	LoadTextureFromFile(aPathToTexture);
}

CSpriteAnimated::~CSpriteAnimated()
{
}

void CSpriteAnimated::SetSpriteSize(const glm::uvec2& aSize)
{
	m_SpriteSize = aSize;
}

glm::uvec2 CSpriteAnimated::GetSpriteSize()
{
	return m_SpriteSize;
}


