#ifndef CMUSIC_TRACK_H_
#define CMUSIC_TRACK_H_

#include <string>
// TODO
//#include "SDL2/SDL_mixer.h"

class CMusicTrack
{
public:
	CMusicTrack(const std::string& a_ID, const std::string& a_Path);
	virtual ~CMusicTrack();

	bool Load();
	bool IsLoaded();

	void Play(int a_Loops = 0);
	void Stop();

	void SetVolume(int a_Volume);
	int GetVolume(int a_Volume);

	bool IsPlaying();

	const std::string& GetID();

private:
	//TODO Mix_Music* 	m_Music;
	int			m_Volume;
	bool		m_Playing;
	std::string	m_ID;
	std::string m_Path;
};

#endif
