#ifndef CSOUNDMANAGER_H_
#define CSOUNDMANAGER_H_

#include "ISubSystem.h"
#include <map>
#include <string>

class CSoundEffect;
class CMusicTrack;
struct SDL_mutex;

void OnSoundStop(int a_Channel);

class CSoundManager: public ISubSystem
{
public:
	typedef std::map< int, CSoundEffect* > t_PlayingSnds;

	CSoundManager();
	virtual ~CSoundManager();

	void StartUp(void);
	void ShutDown(void);
	void Update(float dt);

	void PlaySound(const std::string& a_ID, int a_Loops = 0);
	void StopSound(const std::string& a_ID);
	void StopSounds();

	void PlayMusic(const std::string& a_ID, int a_Loops = 0);
	void StopMusic();

	void Mute();

	void SetMusicVolume(int a_Volume);
	int GetMusicVolume();

	const std::string& GetPlayingTrack();
	std::vector< std::string > GetPlayingSounds();

private:
	friend void OnSoundStop(int a_Channel);
	void StopSound(int a_Channel);

	CMusicTrack*	m_CurrentTrack;
	std::string		m_CurrentTrackID;
	t_PlayingSnds	m_PlayingSnds;
	int				m_MusicVolume;
	SDL_mutex*		m_SndMutex;
};

#endif /* CSOUNDMANAGER_H_ */
