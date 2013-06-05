#ifndef CSOUND_EFFECT_H_
#define CSOUND_EFFECT_H_

#include <string>
#include "CRefCounter.h"
//#include "SDL2/SDL_mixer.h"

class CSoundEffect : public CRefCounter
{
public:
	CSoundEffect(const std::string& a_ID, const std::string& a_Path);
	CSoundEffect(const CSoundEffect& a_Other);
	virtual ~CSoundEffect();

	bool Load();
	void UnLoad();
	bool IsLoaded();

	void SetVolume(int a_Volume);
	int GetVolume(int a_Volume);

	const std::string& GetID();
	//TODO Mix_Chunk* GetChunk();

private:
	//TODO Mix_Chunk* 	m_Chunk;
	int			m_Volume;
	std::string	m_ID;
	std::string	m_Path;
};

#endif

