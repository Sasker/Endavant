#ifndef CSPRITEANIMATED_H_
#define CSPRITEANIMATED_H_
#include "Renderer/Base_Nodes/CTextureNode.h"
#include "Time/CTimeManager.h"

class CSpriteAnimated : public CTextureNode
{
public:
		CSpriteAnimated();

	void		InitSprite(const std::string &aPathToTexture);
	void		InitSprite(const std::string &aPathToTexture, const u32 aNumFrames );
	void		InitSprite(const std::string &aPathToTexture, const u32 aCols, const u32 aRows, const u32 aNumFrames );
	void		InitSprite(const std::string &aPathToTexture, const u32 aCols, const u32 aRows, const u32 aNumFrames, const f32 aSpeed);

	void		SetSpriteSize(const glm::uvec2 &aSize);
	glm::uvec2	GetSpriteSize();

	virtual ~CSpriteAnimated();

private:

	void		FrameTimer(EV_TimerID aTimerID);

	// Height and width of the sprite being rendered
	glm::uvec2	m_SpriteSize;

	s32 		m_indexAnimation;
	f32			m_speedAnimation;

};

#endif /* CSPRITE_H_ */
