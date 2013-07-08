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
	m_indexAnimation = 0;
	m_filas = 0;
	m_columnas = 0;
	m_speedAnimation = 0.0f;
}

void CSpriteAnimated::InitSprite(const std::string& aPathToTexture, int filas, int columnas)
{
	LoadTextureFromFile(aPathToTexture);
	m_indexAnimation = 0;
	m_filas = filas;
	m_columnas = columnas;
	m_speedAnimation = 0.1f;
}

void CSpriteAnimated::InitSprite(const std::string& aPathToTexture, int filas, int columnas, float speed)
{
	LoadTextureFromFile(aPathToTexture);
	m_indexAnimation = 0;
	m_filas = filas;
	m_columnas = columnas;
	m_speedAnimation = speed;
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


