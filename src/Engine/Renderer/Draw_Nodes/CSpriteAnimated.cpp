#include "CSpriteAnimated.h"
#include "GLLoad/GLFuncs.h"

#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"

CSpriteAnimated::CSpriteAnimated():
CTextureNode(),
m_SpriteSize(0,0)
{
	m_TimerID = 0;
	m_speedAnimation = 0.1f;
}

void CSpriteAnimated::InitSprite(const std::string& aPathToTexture)
{
	LoadTextureFromFile(aPathToTexture);
}

void CSpriteAnimated::InitSprite(const std::string& aPathToTexture, const u32 aNumFrames)
{
	LoadTextureFromFile(aPathToTexture, aNumFrames, 1, aNumFrames);
	m_speedAnimation = 0.25f;
	if (aNumFrames > 1)
		m_TimerID  = CCoreEngine::Instance().GetTimerManager().CreateTimer(m_speedAnimation,true );
}

void CSpriteAnimated::InitSprite(const std::string& aPathToTexture, const u32 aNumFrames, const f32 aSpeed)
{
	LoadTextureFromFile(aPathToTexture, aNumFrames, 1, aNumFrames);
	m_speedAnimation = aSpeed;
	if (aNumFrames > 1)
		m_TimerID  = CCoreEngine::Instance().GetTimerManager().CreateTimer(m_speedAnimation,true );
}

void CSpriteAnimated::InitSprite(const std::string& aPathToTexture, const u32 aCols, const u32 aRows, const u32 aNumFrames)
{
	LoadTextureFromFile(aPathToTexture, aCols, aRows, aNumFrames);
	m_speedAnimation = 0.25f;
	if (aNumFrames > 1)
		m_TimerID  = CCoreEngine::Instance().GetTimerManager().CreateTimer(m_speedAnimation,true );
}

void CSpriteAnimated::InitSprite(const std::string& aPathToTexture, const u32 aCols, const u32 aRows, const u32 aNumFrames, const f32 aSpeed)
{
	LoadTextureFromFile(aPathToTexture, aCols, aRows, aNumFrames);
	m_speedAnimation = aSpeed;
	if (aNumFrames > 1)
		m_TimerID  = CCoreEngine::Instance().GetTimerManager().CreateTimer(m_speedAnimation,true );
}

void CSpriteAnimated::Update(f64 dt)
{
	if (m_TimerID)
	{
		if ( CCoreEngine::Instance().GetTimerManager().IsEndTimer(m_TimerID) )
		{
			FrameIncrement();
		}
	}
	CTextureNode::Update( dt);
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
